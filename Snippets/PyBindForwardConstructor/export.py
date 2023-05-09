import ExportAccessor

creator = ExportAccessor.AccessorDerived.Creator("Example", 1, 2)

p = ExportAccessor.Properties()
a = p.Set(creator)

# Access from properties
print("Querying accessor through properties")
p.GetProps()

# Access from the accessor
print("Querying accessor directly")
a.GetProps()
