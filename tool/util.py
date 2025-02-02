import os
from rich.console import Console

def print_styled_error(console: Console, log: str):
    log = log.strip().split('\n')
    for line in log[:-2]:
        split_line = line.split()
        style = 'dim'
        if not split_line:
            print('')
            continue
        if split_line[0] == "Command:":
            style = 'dim'
        elif split_line[0] == "Warning:":
            style = 'red'
        elif split_line[0] in ["Error:", ">>>", "cpp:"]:
            style = 'bold red'

        console.print(line, style=style)


def get_materials_path(mats: [str]):
    materials_path = os.path.join('src', 'materials')
    all_materials = os.listdir(materials_path)
    material_patterns = []
    for m in mats:
        if m not in all_materials:
            raise FileNotFoundError(m)
        material_patterns.append(os.path.join(materials_path, m))
    return material_patterns


def create_pack_manifest(config: dict) -> dict:
    return {
        'format_version': 2,
        'header': {
            "name": config['name'],
            "description": config['description'],
            "uuid": config['uuid'],
            "version": config['version'],
            "min_engine_version": config['min_supported_mc_version']
        },
        'modules': [
            {
                'type': 'resources',
                'uuid': 'eb673f36-e607-48f0-b594-dd24576b413f',
                'version': config['version']
            }
        ],
        'settings': [
            {
                'type': 'label',
                'text': config['custom']['label']
            }
        ],
        'subpacks': [],
        'metadata': {
            'authors': config['authors'],
            'url': config['url']
        }
    }