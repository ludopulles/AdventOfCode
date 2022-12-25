#!/usr/bin/python3
import json, sys
import numpy as np
from datetime import datetime

import matplotlib.pyplot as plt
from matplotlib.patches import Polygon, Rectangle
from matplotlib.lines import Line2D

if len(sys.argv) >= 2 and (sys.argv[1] == '-h' or sys.argv[1] == '--help'):
    sys.exit(f'Usage: {sys.argv[0]} [json-file] [day]')

json_file = str(datetime.now().year) + '.json' if len(sys.argv) < 2 else sys.argv[1]
day_limit = 25 if len(sys.argv) < 3 else int(sys.argv[2])

with open(json_file, 'r') as myfile:
    data = json.loads(myfile.read())

OFFSET = int((datetime(int(data['event']),12,1) - datetime(1970,1,1)).total_seconds())
MARKERS = 'DXos'
MARKERSIZES = [5,6,5,5]
COLORS = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red', 'tab:purple', 'tab:brown', 'tab:pink', 'tab:gray', 'tab:olive', 'tab:cyan']

scores = data['members']
results = {}

for x in scores.values():
    name = x['name']
    res = {}
    for day,submissions in filter(lambda x: int(x[0]) <= day_limit, x['completion_day_level'].items()):
        d = int(day)
        res[d] = (
            (int(submissions['1']['get_star_ts'])-OFFSET)/60/60 + 1-24*(d-1) if '1' in submissions else None,
            (int(submissions['2']['get_star_ts'])-OFFSET)/60/60 + 1-24*(d-1) if '2' in submissions else None
        )
    results[str(name)] = res
    #print(str(name), ','.join('{}:({},{})'.format(
    #    d,
    #    '{}:{}:{}'.format(int(s1//1), int(((s1*60)%60)//1), int(((s1*3600)%60)//1)) if s1 is not None else 'None',
    #    '{}:{}:{}'.format(int(s2//1), int(((s2*60)%60)//1), int(((s2*3600)%60)//1)) if s2 is not None else 'None'
    #) for d,(s1,s2) in sorted(res.items())))

fig = plt.figure(figsize=(11,10))
ax = fig.gca()
w = 1
points = sum([[ [w*(1-(x-1)/27), x], [w*(1-(x+1)/27), x+1] ] for x in range(1,27)], [])
symm_ps = np.array(points + [[-x,y] for x,y in reversed(points[:-1])])
ax.add_patch(Rectangle([-w/18,0], w/9, 3, color='#433525'))
ax.add_patch(Polygon(symm_ps, color='darkgreen', linewidth=0))

ax.add_line(Line2D([0,0],[27,28], color='y'))
ax.plot([0],[28], marker='*', markersize=30, color='y')

line_endpoints = []
for x in range(1,26):
    line_endpoints.append(([-w*(1-x/27),w*(1-(x+1)/27)],[x,x+1]))
    ax.add_line(Line2D(*line_endpoints[-1], linewidth=1, color='y'))
ax.set_xlim((-w,w))
ax.set_ylim((0,29))

for i,(name,res) in enumerate(sorted(results.items(), key=lambda x : x[0].lower())):
    if not res: continue
    for j in range(2):
        xs,ys = zip(*[(x[j],d) for d,x in sorted(res.items()) if x[j] is not None])
        newxs,newys = [],[]
        for x,y in filter(lambda z: 6 <= z[0] <= 24, zip(xs,ys)):
            [x1,x2],[y1,y2] = line_endpoints[y-1]
            t = (x-6)/18
            newxs.append(x1 + t * (x2 - x1))
            newys.append(y1 + t * (y2 - y1))
        color = COLORS[i%len(COLORS)]
        marker = MARKERS[i//len(COLORS)]
        markersize = MARKERSIZES[i//len(COLORS)]
        ax.plot(newxs, newys, marker=marker, markersize=markersize, linestyle='', color=color, label=name if j == 0 else None, zorder=10)
        if len(newxs) == 25:
            newxs += [0]
            newys += [27]
        ax.plot(newxs, newys, color=color, linestyle='--' if j == 1 else '-', alpha=.5)

box = ax.get_position()
ax.set_position([box.x0 + .12*box.width, box.y0, .95*box.width, box.height])
fig.subplots_adjust(left=.2,right=.95,top=.95,bottom=.05)
fig.legend(loc='center left', framealpha=1, bbox_to_anchor=(.02,.5))
ax.axis('off')
fig.savefig('tree.png')
#plt.show()


# Scores:
fig = plt.figure(figsize=(15,8))
ax = fig.gca()
ax.set_xlim((6,24))
ax.set_ylim((0,26))
for i in range(1,26):
    ax.plot([6,24],[i,i], color = 'k')
for i,(name,res) in enumerate(sorted(results.items(), key = lambda x : x[0].lower())):
    if not res: continue
    for j in range(2):
        xs,ys = zip(*[(x[j],d) for d,x in sorted(res.items()) if x[j] is not None])
        color = COLORS[i%len(COLORS)]
        marker = MARKERS[i//len(COLORS)]
        markersize = MARKERSIZES[i//len(COLORS)]
        ax.plot(xs, ys, marker = marker, markersize = markersize, linestyle = '', color = color, label = name if j == 0 else None, zorder = 10)
        ax.plot(xs, ys, color = color, linestyle = '--' if j == 1 else '-', alpha = .3, linewidth = 1.5)

box = ax.get_position()
ax.set_position([box.x0 + .12*box.width, box.y0, .95*box.width, box.height])
fig.legend(loc = 'center left', framealpha=1, bbox_to_anchor = (.02,.5))

xticks = [6,12,18,24]
yticks = range(1,26)
ax.set_xticks(xticks)
ax.set_xticklabels(map(lambda x : '{}:00'.format(x%24), xticks))
ax.set_yticks(yticks)
ax.set_yticklabels(map(lambda y : 'Day {}'.format(y), yticks))
ax.set_xlabel('Local time')
fig.savefig('table.png')
#plt.show()

