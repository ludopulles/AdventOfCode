#!/usr/bin/python3
import datetime, json, sys

if len(sys.argv) != 2 and len(sys.argv) != 3:
    exit("Usage: " + sys.argv[0] + " [day] <json-file>\n")

curday = int(datetime.datetime.now().strftime("%d"))
if len(sys.argv) == 3:
    curday = int(sys.argv[1])

# read file
with open(sys.argv[-1], 'r') as myfile:
    data = json.loads(myfile.read())

members = data['members']
ids = members.keys()
names = dict([ (_id, members[_id]['name']) for _id in ids ])
scores = dict([ (_id, 0) for _id in ids ])

def delta_t(_id, day):
    solves = members[_id]['completion_day_level']
    if str(day) not in solves:
        return None
    today = solves[str(day)]
    if '2' not in today:
        return None
    return (today['2']['get_star_ts'] - today['1']['get_star_ts'], _id)

def hms(t):
    if t is None:
        return ""
    return (("" if t[0] < 3600 else str(t[0]//3600) + "h")
        + ("" if t[0] < 60 else str((t[0]//60)%60) + "m")
        + str(t[0]%60) + "s")

def scoring(rank): # rank is zero based.
    N = len(members)
    return pow(N, 1.0 - rank / (N - 1))
    # return len(members) - rank


for day in range(1, curday + 1):
    times = sorted(filter(None, [ delta_t(_id, day) for _id in ids ]))
    ranks = []
    lasttime = -1
    for (time, _id) in times:
        # Tie: give same score
        ranks.append(ranks[-1] if time == lasttime else len(ranks))
        lasttime = time
    for i in range(len(ranks)):
        scores[times[i][1]] += scoring(ranks[i])

deltas = dict([ (times[i][1], scoring(ranks[i])) for i in range(len(ranks)) ])
fscores = sorted(scores.items(), key=lambda x: -x[1])
deltatimes = [ hms(delta_t(x[0], curday)) for x in fscores ]
W = max(4, max(map(len, deltatimes)))

print("Day ", curday, "\nRank |  Score |  Delta | ",
    ("{:>" + str(W) + "}").format("time"),
    " | Name", sep="")
for i in range(len(fscores)):
    if fscores[i][1] == 0:
        continue
    _id = fscores[i][0]
    d = f"{deltas[_id]:+.2f}" if _id in deltas else ""
    s = round(fscores[i][1], 2)
    print(f"{i+1:>4} | {fscores[i][1]:>6.2f} | {d:>6} | ",
            ("{:>" + str(W) + "}").format(deltatimes[i]),
            " | ", names[fscores[i][0]], sep="")
print()
