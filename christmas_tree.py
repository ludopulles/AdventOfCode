#!/usr/bin/python3
import datetime, json, sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.lines import Line2D

if len(sys.argv) != 2:
    exit("Usage: " + sys.argv[0] + " <json-file>\n")

with open(sys.argv[-1], 'r') as myfile:
    data = json.loads(myfile.read())

OFFSET = int((datetime.datetime(2021,12,1)-datetime.datetime(1970,1,1)).total_seconds())
MARKERS = 'DXos'
MARKERSIZES = [5,7,5,5]
COLORS = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red', 'tab:purple', 'tab:brown', 'tab:pink', 'tab:gray', 'tab:olive', 'tab:cyan']
UK = ['MrGuenst']

scores = data['members']
results = {}

for x in scores.values():
    name = x['name']
    res = {}
    for day,submissions in x['completion_day_level'].items():
        d = int(day)
        res[d] = (
            (int(submissions['1']['get_star_ts'])-OFFSET)/60/60-24*(d-1)+(1 if name not in UK else 0) if '1' in submissions else None,
            (int(submissions['2']['get_star_ts'])-OFFSET)/60/60-24*(d-1)+(1 if name not in UK else 0) if '2' in submissions else None
        )
    results[str(name)] = res
    print(str(name), ','.join('{}:({},{})'.format(
        d,
        '{}:{}:{}'.format(int(s1//1), int(((s1*60)%60)//1), int(((s1*3600)%60)//1)) if s1 is not None else "None",
        '{}:{}:{}'.format(int(s2//1), int(((s2*60)%60)//1), int(((s2*3600)%60)//1)) if s2 is not None else "None"
    ) for d,(s1,s2) in sorted(res.items())))

fig = plt.figure(figsize=(11,10))
ax = fig.gca()
w = 27
points = [[0,0],[.5,0],[.5,1]] + sum([[
    [w*(1-(x-1)/27), x],
    [w*(1-(x+1)/27), x+1]
]
for x in range(1,27)], [])
symm_ps = np.array(points + [[-x,y] for x,y in reversed(points[1:-1])])
ax.add_patch(Polygon(symm_ps, color = 'darkgreen'))
line_endpoints = []
for x in range(1,26):
    line_endpoints.append(([-w*(1-x/27),w*(1-(x+1)/27)],[x,x+1]))
    ax.add_line(Line2D(*line_endpoints[-1], color = 'y'))
ax.add_line(Line2D([0,0],[27,27.5], color = 'k'))
ax.set_xlim((-27,27))
ax.set_ylim((0,28.5))

for i,(name,res) in enumerate(sorted(results.items(), key = lambda x : x[0].lower())):
    if not res: continue
    for j in range(2):
        xs,ys = zip(*[(x[j],d) for d,x in sorted(res.items()) if x[j] is not None])
        newxs,newys = [],[]
        for x,y in zip(xs,ys):
            [x1,x2],[y1,y2] = line_endpoints[int(y)-1]
            t = (x-6)/18
            if not 0 <= t <= 1: continue
            newx,newy = x1+t*(x2-x1),y1+t*(y2-y1)
            newxs.append(newx)
            newys.append(newy)
        color = COLORS[i%len(COLORS)]
        marker = MARKERS[i//len(COLORS)]
        markersize = MARKERSIZES[i//len(COLORS)]
        # if name == 'noahiscool13': ax.plot([0],[28], marker = marker, markersize = 10, color = color)
        # if name == 'Olaf Erkemeij': ax.plot([0],[27.5], marker = marker, markersize = 10, color = color)
        ax.plot(newxs, newys, marker = marker, markersize = markersize, linestyle = '', color = color, label = name if j == 0 else None, zorder = 10)
        # ax.plot(newxs + [0] if name in ['noahiscool13','Olaf Erkemeij'] else [], newys + [28 if name == 'noahiscool13' else 27.5] if name in ['noahiscool13','Olaf Erkemeij'] else [], color = color, linestyle = '--' if j == 1 else '-', alpha = .2)
        ax.plot(newxs, newys, color = color, linestyle = '--' if j == 1 else '-', alpha = .2)

box = ax.get_position()
ax.set_position([box.x0 + .12*box.width, box.y0, .95*box.width, box.height])
fig.subplots_adjust(left=.2,right=.95,top=.95,bottom=.05)
fig.legend(loc = 'center left', framealpha=1, bbox_to_anchor = (.02,.5))
ax.axis('off')
fig.savefig('tree.png')
plt.show()

