import oppai

with oppai.OppaiWrapper() as ezpp: # has __enter__ and __exit__ to manage c memory for you
  ezpp.configure(mode=0, acc=99.83, mods=16, combo=2430, nmiss=0) # positional is optional, but must be provided in this order if not
  ezpp.calculate("map.osu") # you can also pass bytes to ezpp.calculate_data(bytes)
  
  pp = ezpp.get_pp()
  sr = ezpp.get_sr()

print(sr, pp)