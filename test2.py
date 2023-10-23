from akatsuki_pp_py import Beatmap, Calculator

map = Beatmap(path = "map.osu")
calc = Calculator(mods = 8)

# Calculate an SS on HD
max_perf = calc.performance(map)

# The mods are still set to HD
calc.set_acc(94.82)
calc.set_n_misses(0)
calc.set_combo(4285)

# A good way to speed up the calculation is to provide
# the difficulty attributes of a previous calculation
# so that they don't need to be recalculated.
# **Note** that this should only be done if neither
# the map, mode, mods, nor passed objects amount changed.
calc.set_difficulty(max_perf.difficulty)

curr_perf = calc.performance(map)
print(f'PP: {curr_perf.pp}/{max_perf.pp} | Stars: {max_perf.difficulty.stars}')

map_attrs = calc.map_attributes(map)
print(f'BPM: {map_attrs.bpm}')

strains = calc.strains(map)
print(f'Maximum aim strain: {max(strains.aim)}')