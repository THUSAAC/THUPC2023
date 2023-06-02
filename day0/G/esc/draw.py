import svg
import random

def draw() ->svg.SVG:
    n=int(input())
    a = list(map(int,input().split()))
    last=[0 for i in range(n)]
    for id,x in enumerate(a):
        last[x] = id
    xs = []
    ys = []
    xt = []
    yt = []
    r = []
    g = []
    b = []
    for id,x in enumerate(a):
        if(last[x]!=id):
            r.append(random.randint(0,155))
            g.append(random.randint(0,155))
            b.append(random.randint(0,155))
            ys.append(7800)
            xs.append((id+1)*10)
            yt.append(7800)
            xt.append((last[x]+1)*10)
    return svg.SVG(
        width=16000,height=8000,color="white",elements=[
            svg.Path(
                stroke="rgb("+str(r[i])+","+str(g[i])+","+str(b[i])+")",
                stroke_width=3,
                d=[svg.MoveTo(x=xs[i],y=ys[i]),svg.Arc(rx=(xt[i]-xs[i])/2,ry=(xt[i]-xs[i])/2,angle=180,x=xt[i],y=yt[i],large_arc=False,sweep=True)],
                fill="none"
            )for i in range(n//2)
        ],
    )

print(draw())
