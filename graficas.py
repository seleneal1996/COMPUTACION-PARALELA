import matplotlib.pyplot as plt
from math import log as ln
from matplotlib.pyplot import figure
x=[]
y=[]
y1=[]
y2=[]
tam_vec = [100,200,300]

for i in tam_vec:
  x.append(i)
for i in [0.011, 0.093 , 0.324]:
                      y.append(i)
for i in [0.333044,	2.03844,6.65431]:
                  y1.append(i)
for i in tam_vec:
  y2.append(ln(i)*i)


plt.plot(x,y,color ='b',label='MULTIPLICACION MATRIX CLASICA')
plt.plot(x,y1,color ='y',label='MULTIPLICACION VERSION POR BLOQUES')


plt.grid(True)
plt.legend()
plt.xlabel('n')
plt.ylabel('times')