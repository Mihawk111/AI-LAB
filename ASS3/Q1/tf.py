C=[[4,1,8,6,3,2,5,8,6,7],[4,1,8,6,7,9,3,1,2,3.6],[4,1,8,6,3,2,5,8,6,7],[4,1,8,6,7,9,3,1,2,3.6]]

beta=[0.1,0.2,0.2,0.4,0.4,0.6,0.3,0.7,0.5,0.5]

max=[]
mval=-100000

for i in range(11):
    for j in range(11):
        for k in range(11):
            for l in range(11):
                x=[i,j,k,l]
                f=0

                for m in range(10):
                    denom=0
                    for n in range(4):
                        p=(x[n]-C[n][m])
                        denom+=p*p
                    f+=1/(denom+beta[m])
                
                f=-f

                if(f>mval):
                    max[:]=x[:]
                    mval=f

print(max)