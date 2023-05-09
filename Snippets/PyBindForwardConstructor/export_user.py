import ExportAccessor

def _CreateAccessor(self, AccessorType, properties, *args, **kargs):
    creator = ExportAccessor.AccessorDerived.Creator(*args)
    a = p.Set(creator)
    return a 

ExportAccessor.Properties.CreateAccesor = _CreateAccessor

p = ExportAccessor.Properties()
a = p.CreateAccesor(ExportAccessor.AccessorDerived, p, "ExampleAccesor", 1, 2)

# Access from properties
print("Querying accessor through properties")
p.GetProps()

# Access from the accessor
print("Querying accessor directly")
a.GetProps()
