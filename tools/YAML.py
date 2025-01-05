import os
import yaml

book_structure = {
    "project": {
        "type": "book"
    },
    'book': {
        'title': "{SLmetrics} Docs",
        'author': "Norah Jones",
        'date': "1/5/2025",
        'chapters': [
            'index.qmd',
            'intro.qmd',
            'summary.qmd',
            {
                'part': "References",
                'chapters': []
            }
        ]
    },
    'bibliography': 'references.bib',
    'format': {
        'html': {'theme': {
            "light": "flatly",
            "dark":  "flatly"
        }},
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