import inspect
import importlib

import base

def isfrommod(mod, mod_name):
    return mod.__module__ == mod_name

def isstage(mod, mod_name):
    return inspect.isclass(mod) and isfrommod(mod, mod_name) and issubclass(mod, base.BaseStage) == True

def discoverstages(to_load):
    protos = []

    for mod_name in to_load:
        mod = importlib.import_module(mod_name)

        possible_stages = [{"name": name, "cls_proto": mod_cls} for name, mod_cls in mod.__dict__.items() if isstage(mod_cls, mod_name)]

        match len(possible_stages):
            case 0:
                print(f"No stages present in module {mod_name}")
            case 1:
                print(f"Dicovered {mod_name}.{possible_stages[0]['name']}")
                yield possible_stages[0]['cls_proto']
            case _:
                print(f"Too many classes {[p['name'] for p in possible_stages]} have the 'stage' attribute")


if __name__ == "__main__":

    to_load = [
        "user_1",
        "user_2",
        "user_3",
        "user_4",
        "user_5"
    ]

    for cls_proto in discoverstages(to_load):
        instance = cls_proto()