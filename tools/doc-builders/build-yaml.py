import os
import re
import yaml

class YAML:
    def __init__(self, docs_dir="docs"):
        self.root_dir = os.path.abspath(os.path.join(os.getcwd(), docs_dir, ".."))
        self._version = self.get_version()
        os.chdir(os.path.join(os.getcwd(), docs_dir))

        self.book_structure = {
            "project": {
                "type": "book"
            },
            'book': {
                'title': "{SLmetrics}: Machine Learning Performance Evaluation on Steroids",
                'subtitle': f"Version {self._version}",
                'author': "Serkan Korkmaz",
                'version': self._version,
                'repo-url': "https://github.com/serkor1/SLmetrics",
                'repo-branch': "development",
                'repo-subdir': "docs",
                'repo-actions': ["edit", "source", "issue"],
                'sharing': ["twitter", "facebook", "linkedin"],
                'sidebar': {
                    'title': "Documentation"
                },
                'downloads': ['pdf', 'epub'],
                'chapters': [
                    'index.qmd',
                    'intro.qmd',
                    'summary.qmd',
                    'benchmark.qmd',
                    {
                        'part': 'regression_functions.qmd',
                        'chapters': [],
                        'number-sections': False
                    },
                    {
                        'part': 'classification_functions.qmd',
                        'chapters': [],
                        'number-sections': False
                    },
                    "garbage.qmd",
                    "references.qmd"
                ]
            },
            'bibliography': 'references.bib',
            'format': {
                'html': {
                    'theme': {
                        "light": ["cosmo", "theme-light.scss"],
                        "dark": ["slate", "theme-dark.scss"]
                    },
                    "fontsize": "18px",
                    "mainfont": "calibri"
                },
                'pdf': {
                    'documentclass': 'scrreprt',
                    'keep-tex': True,
                    'latex-auto-install': True
                    }
            },
            'highlight-style': "github",
            "execute": {
                "freeze": "auto",
                "cache": True
            }
        }

    def get_version(self):
        desc_path = os.path.join(self.root_dir, "DESCRIPTION")
        with open(desc_path, 'r') as file:
            content = file.read()
        match = re.search(r'^Version:\s*(\S+)', content, re.MULTILINE)
        return match.group(1) if match else "0.0.0"

    def locate_part(self, part_filename: str) -> int:
        chapters = self.book_structure['book']['chapters']
        return next(
            (index for index, item in enumerate(chapters)
             if isinstance(item, dict) and item.get('part') == part_filename),
            -1
        )

    def gather_references_in_dir(self, directory: str) -> list:
        if not os.path.isdir(directory):
            return []
        files = [f for f in os.listdir(directory) if f.endswith('.qmd')]
        files.sort()  # sorts in place; alphabetical
        # Join directory name with each file to get a relative path
        return [os.path.join(directory, f) for f in files]

    def add_chapters(self, part_filename: str, chapters: list):
        idx = self.locate_part(part_filename)
        if idx == -1:
            print(f"[WARNING] The part '{part_filename}' was not found; skipping assignment.")
            return
        self.book_structure['book']['chapters'][idx]['chapters'] = chapters

    def build(self):
        try:
            reg_references = self.gather_references_in_dir("ref_regression")
            self.add_chapters("regression_functions.qmd", reg_references)

            cls_references = self.gather_references_in_dir("ref_classification")
            self.add_chapters("classification_functions.qmd", cls_references)

        except Exception as e:
            print(f"[ERROR] Could not build references: {str(e)}")
            print("Skipping reference assignment...")

    def write_config(self, output_file="_quarto.yaml"):
        with open(output_file, 'w') as f:
            yaml.dump(self.book_structure, f, sort_keys=False)
        print(f"Successfully wrote {output_file} in {os.getcwd()}")


if __name__ == "__main__":
    # 1) initiate YAML
    builder = YAML(docs_dir="docs")

    # 2) build YAML
    builder.build()

    # 3) store YAML as "_quarto.yaml" in docs/
    builder.write_config("_quarto.yaml")
