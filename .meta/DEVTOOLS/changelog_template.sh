#!/usr/bin/env bash
set -euo pipefail

## 1) define constant
##    values across the shell
##    script
DESCRIPTION_FILE="DESCRIPTION"
CHANGELOG_DIR=".meta/CHANGELOG"
SRC_DIR="${CHANGELOG_DIR}/src"

## 2) define helper-functions
##    for the remaining script

## 2.1) get_meta:
## extracts relevant fields from
## DESCRIPTION
##
## usage: get_meta "Version" corresponding to the
## version field of the Description 
function get_meta() {
    grep '^Version:' "${DESCRIPTION_FILE}" | sed 's/Version: //'
}

## 2.2) do_exist:
## checks if the file already exists
## and prompts for overwriting or not.
function do_exist() {
    local file=$1
    if [ -f "${file}" ]; then
        echo -n "File ${file} already exists. Overwrite? (y/n): "
        read -r answer
        if [[ "${answer}" =~ ^[Yy]$ ]]; then
            echo "Overwriting existing file."
            return 0
        else
            echo "Operation cancelled."
            return 1
        fi
    fi
    return 0
}

## 2.2) template:
## generates the vXXX.qmd
## file pre-populated with relevant chunks
## and template headers
function template() {
    local file=$1
    local version=$2
    
    cat <<EOF > "${file}"
    ---
    format:
    gfm:
        default-image-extension: ".png"
    always_allow_html: true
    execute:
    cache: true
    freeze: auto
    dir: .meta/CHANGELOG
    knitr:
    opts_chunk:
        collapse: true
        comment: "#>"
        dpi: 1280
        fig.height: 6
        out.width: 100%
    ---
    \`\`\`{r install_version ($version)}
    #| echo: false
    #| include: false
    pak::pak(pkg = "serkor1/SLmetrics@v$version", ask = FALSE)
    \`\`\`
    # :bookmark: Version $version

    ## :sparkles: Improvements

    ### :rocket: New features

    ## :bug: Bug-fixes

    ## :boom: Breaking changes
EOF
}

## 3) build (latest) NEWS entry
## 3.1) extract latest version
##      and echo just in case
VERSION=$(get_meta)
echo "Creating changelog entry for version: ${VERSION}"

## 3.2) construct entry path
##      and check if it exists
##      and generate template if not
new_entry="${SRC_DIR}/v${VERSION}.qmd"

## 3.3) does it already exist?
##      yes: exit
##      no: lets goooo!
do_exist "${new_entry}" || exit 1

## 3.4) add template values
##      to the new files
template "${new_entry}" "${VERSION}"

## 4) verbose finished script
echo "✅ Successfully created changelog entry: ${new_entry}"
echo "You can now edit this file to add your changelog details."