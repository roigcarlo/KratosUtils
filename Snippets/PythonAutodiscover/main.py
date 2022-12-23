import sys
import inspect
import importlib

def discover_stages(to_load):
    protos = []

    for custom_mod_name in to_load:
        custom_mod = importlib.import_module(custom_mod_name)

        excl_defined    = [m[0] for m in inspect.getmembers(custom_mod, inspect.isclass) if m[1].__module__ == custom_mod_name]
        
        # excl_defined could be avoided if I could query mod_cls.__module__ == custom_mod_name. But it does not let me do that :S.
        possible_stages = [{"name": name, "cls_proto": mod_cls} for name, mod_cls in custom_mod.__dict__.items() if name in excl_defined and hasattr(mod_cls, "stage") and getattr(mod_cls, "stage") == True]

        match len(possible_stages):
            case 0:
                print(f"No stages present in module {custom_mod_name}")
            case 1:
                print(f"Dicovered {custom_mod_name}.{possible_stages[0]['name']}")
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

    for cls_proto in discover_stages(to_load):
        instance = cls_proto()