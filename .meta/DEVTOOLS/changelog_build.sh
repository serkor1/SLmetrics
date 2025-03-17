#!/usr/bin/env bash
set -euo pipefail

## 1) define constant
##    values across the shell
##    script
DESCRIPTION_FILE="DESCRIPTION"
CHANGELOG_DIR=".meta/CHANGELOG"
SRC_DIR="${CHANGELOG_DIR}/src"
OUTPUT_FILE="${CHANGELOG_DIR}/NEWS.qmd"

## 2) define helper-functions
##    for the remaining script

## 2.1) get_meta:
## extracts relevant fields from
## DESCRIPTION
##
## usage: get_meta "Version" corresponding to the
## version field of the Description 
function get_meta() {
    local field=$1
    grep "^${field}:" "${DESCRIPTION_FILE}" | sed "s/${field}: //"
}

## 2.2) template:
## generates the main .qmd
## file pre-populated with relevant information
function template() {
    local version=$1
    local package=$2
    local output_file=$3

    cat <<-EOF > "${output_file}"
    ---
    format:
        gfm:
            default-image-extension: ".png"
    always_allow_html: true
    execute:
    cache: true
    freeze: auto
    dir: .meta
    knitr:
    opts_chunk:
        collapse: true
        comment: "#>"
        dpi: 1280
        fig.height: 6
        out.width: 100%
    ---
    > Version ${version} is considered pre-release of {${package}}. We do not
    > expect any breaking changes, unless a major bug/issue is reported and its nature
    > forces breaking changes.
EOF
}

## 2.2) render:
## renders ALL .qmd files in the src directory
## corresponds to quarto --render file
function render() {
    local src_dir=$1
    local qmd_files=($(ls "${src_dir}"/*.qmd 2>/dev/null | sort -rV))
    local total_files=${#qmd_files[@]}
    
    if [ ${total_files} -eq 0 ]; then
        echo "No .qmd files found in ${src_dir}"
        return 0
    fi
    
    echo "Rendering ${total_files} .qmd files..."
    
    for i in "${!qmd_files[@]}"; do
        local file="${qmd_files[$i]}"
        local progress=$((i * 100 / total_files))
        local bar_length=$((progress / 2))
        
        
        printf "\r[%-50s] %d%%" "$(printf '#%.0s' $(seq 1 ${bar_length}))" "${progress}"
        
        
        if ! quarto render "${file}" >/dev/null 2>&1; then
            echo -e "\nError rendering ${file}"
            return 1
        fi
    done

    printf "\r[%-50s] %d%%\n" "$(printf '#%.0s' $(seq 1 50))" "100"
    return 0
}

## 2.3) append:
## appends all .md files to the 
## main document with include directives
function append() {
    local src_dir=$1
    local output_file=$2
    
    local md_files=($(ls "${src_dir}"/*.md 2>/dev/null | sort -rV))
    local total_files=${#md_files[@]}
    
    if [ ${total_files} -eq 0 ]; then
        echo "No .md files found in ${src_dir}"
        return 0
    fi
    
    for file in "${md_files[@]}"; do
        local clean_path="${file#.meta/CHANGELOG}"
        echo -e "{{< include ${clean_path} >}}\n" >> "${output_file}"
    done
    
    return 0
}

## 3) build changelog
## 3.1) extract version
##      and package name
VERSION=$(get_meta "Version")
PKGNAME=$(get_meta "Package")

## 3.2) create template
template "${VERSION}" "${PKGNAME}" "${OUTPUT_FILE}"

## 3.3) render all .qmd files
##      exit if fails
render "${SRC_DIR}" || {
    echo "Error in rendering process, exiting."
    exit 1
}

## 3.4) append include directives to the
##      main file
append "${SRC_DIR}" "${OUTPUT_FILE}"

## 4) verbose finished script
echo "✅ Successfully generated ${OUTPUT_FILE}"