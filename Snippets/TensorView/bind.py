import BindModule

def ext_function():
    scoped = BindModule.Dof.GetValueList()

    return scoped

# Get the dofs and print them
result = ext_function()
print(f"Raw Results")
print(f"Result: {[r.GetValue() for r in result]}")

# Modify some dofs
result[0].SetValue(4)
result[1].SetValue(5)
result[2].SetValue(6)

print(f"After using set Results")
print(f"Result: {[r.GetValue() for r in result]}")

BindModule.Dof.ModifyVaList()

print(f"After midify in memory")
print(f"Result: {[r.GetValue() for r in result]}")

# Get the modified dofs again print them
result_m = ext_function()
print(f"After retrieve again")
print(f"Result: {[r.GetValue() for r in result_m]}")