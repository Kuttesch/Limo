from skyfield.api import load, wgs84, N, W


ts = load.timescale()
t = ts.now()

planets = load('de421.bsp')
earth, uwu = planets['earth'], planets['moon']

astrometric = earth.at(t).observe(uwu)
ra, dec, distance = astrometric.radec()

boston = earth + wgs84.latlon(47.866513 * -1, 12.108991 * W)
astrometric = boston.at(t).observe(uwu)
altitude, azimut, d = astrometric.apparent().altaz()

print(altitude.degrees)
print(azimut.degrees)
print(d)
