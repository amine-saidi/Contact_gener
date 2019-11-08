import commands
import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.axes as ax
import glob, os

with  open('./logfile_Post_T') as f1:
    lines    = f1.readlines()
    X1        = np.asarray([float(line.split()[1]) for line in lines[0:]])
    Y0     = np.asarray([float(line.split()[9]) for line in lines[0:]])
    Y1       = np.asarray([float(line.split()[10]) for line in lines[0:]])   
    Y2       = np.asarray([float(line.split()[4]) for line in lines[0:]])   
    Y3       = np.asarray([float(line.split()[5]) for line in lines[0:]])   
    Y4       = np.asarray([float(line.split()[6]) for line in lines[0:]])   
    Y5       = np.asarray([float(line.split()[7]) for line in lines[0:]])   
    Y6       = np.asarray([float(line.split()[8]) for line in lines[0:]])   

plt.figure(figsize=(8,5))

#
X1=X1*2        
plt.figure(figsize=(8,5))
#plt.xlim(0,127)     # set the xlim to left, right
plt.plot(X1, Y0,'-', label='$\lambda_n$')
plt.plot(X1, Y1,'-', label='$\sigma_{22}$')

plt.xscale('log')
plt.yscale('log')
plt.grid(True)
plt.rc('text', usetex=True)
plt.rc('font',**{'family':'serif','serif':['Helvetica']} )
plt.rc('font', size=14)
plt.xlabel(r'Taille de maille(mm)')
plt.ylabel(r'Qual.solution pression(%)')
plt.legend(loc='upper right',fontsize=18,numpoints=1)
#plt.show()
plt.tight_layout()
plt.savefig('./Qua_Solu.pdf')


# ////////////////////////////





plt.figure(figsize=(8,5))

#
        
plt.figure(figsize=(8,5))
#plt.xlim(0,127)     # set the xlim to left, right
plt.plot(X1, abs((Y2-Y3)/Y3),'-', label='semi largeur de contatc ')
plt.plot(X1, X1/Y3,'-', label='limite theorique maximale ')

plt.xscale('log')
plt.yscale('log')
plt.grid(True)
plt.rc('text', usetex=True)
plt.rc('font',**{'family':'serif','serif':['Helvetica']} )
plt.rc('font', size=14)
plt.xlabel(r'Taille de maille(mm)')
plt.ylabel(r'erreur relatif')
plt.legend(loc='upper right',fontsize=18,numpoints=1)
#plt.show()
plt.tight_layout()
plt.savefig('./Errer_A.pdf')


plt.figure(figsize=(8,5))

#
        
plt.figure(figsize=(8,5))
#plt.xlim(0,127)     # set the xlim to left, right
plt.plot(X1, abs((Y4-Y6)/Y6),'-', label='$\lambda_n$')
plt.plot(X1, abs((Y5-Y6)/Y6),'-', label='$\sigma_{22}$')

plt.xscale('log')
plt.yscale('log')
plt.grid(True)
plt.rc('text', usetex=True)
plt.rc('font',**{'family':'serif','serif':['Helvetica']} )
plt.rc('font', size=14)
plt.xlabel(r'Taille de maille(mm)')
plt.ylabel(r'erreur relatif')
plt.legend(loc='upper right',fontsize=18,numpoints=1)
#plt.show()
plt.tight_layout()
plt.savefig('./Erreur_Pmax.pdf')







