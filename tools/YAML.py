import os
import yaml
import re

def version():
    # 1) open DESCRIPTION
    with open("DESCRIPTION", 'r') as file:
        content = file.read()

    # 2) find path from
    return re.search(r'^Version:\s*(\S+)', content, re.MULTILINE).group(1)


book_structure = {
    "project": {
        "type": "book"
    },
    'book': {
        'title': "{SLmetrics}: Machine Learning Performance Evaluation on Steroids",
        'subtitle': f"Version {version()}",
        'author': "Serkan Korkmaz",
        'version': version(),
        'repo-url': "https://github.com/serkor1/SLmetrics",
        'repo-actions': ["edit", "source", "issue"],
        'sharing': ["twitter", "facebook", "linkedin"],
        'sidebar':{
            'title': "Documentation"
        },
        'chapters': [
            'index.qmd',
            'intro.qmd',
            'summary.qmd',
            'benchmark.qmd',
            {
                'part': "metrics",
                'chapters': []
            },
            "references.qmd"
        ]
    },
    'bibliography': 'references.bib',
    'format': {
        'html': {
            'theme': {
            "light": "cosmo",
            "dark":  "darkly"
        }
        },
        'pdf': {'documentclass': 'scrreprt'}
    },
    "execute": {
        "freeze": "auto"
    }
}

try:
    references_dir = 'references'
    reference_files = [f for f in os.listdir(references_dir) if f.endswith('.qmd')]
    reference_files.sort()
    reference_files = [os.path.join(references_dir, f) for f in reference_files]
    book_structure['book']['chapters'][3]['chapters'] = reference_files
except:
    print("No references found! Skipping")


with open('docs/_quarto.yml', 'w') as file:
    yaml.dump(book_structure, file, sort_keys=False)