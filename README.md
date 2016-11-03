# first-project
Euler exercise 1
m=1
z=0
while m<354295:
    m+=1
    y=str(m)
    if len(y)==6:
      z=(int(y[0]))**5+(int(y[1]))**5+(int(y[2]))**5+(int(y[3]))**5+(int(y[4]))**5+(int(y[5]))**5
    if len(y)==5:
      z=(int(y[0]))**5+(int(y[1]))**5+(int(y[2]))**5+(int(y[3]))**5+(int(y[4]))**5
    if len(y)==4:
      z=(int(y[0]))**5+(int(y[1]))**5+(int(y[2]))**5+(int(y[3]))**5
    if len(y)==3:
      z=(int(y[0]))**5+(int(y[1]))**5+(int(y[2]))**5
    if len(y)==2:
      z=(int(y[0]))**5+(int(y[1]))**5
    if len(y)==1:
      z=(int(y[0]))**5
    if m==z:
        print (m)
