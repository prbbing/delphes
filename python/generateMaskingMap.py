import os,sys
import numpy as np
from math import *
from random import *
import ROOT as r

outf = r.TFile("deadCellMap.root", "RECREATE")
os.system("touch deadCellMap.txt")
mapEtaf = open("deadCellEta.txt", "w")
mapPhif = open("deadCellPhi.txt", "w")
outf.cd()
mapHist = r.TH2D("map","map", 120,-3,3, 128,-3.2,3.2)

# Create eta-phi grid assuming 0.0175 X 0.0175 granularity 
eta = np.arange(-3, 3, 0.0175, dtype=float)
phi = np.arange(-pi, pi, 0.0175, dtype=float)

maskedEtaPhi = []

# Pick 1% of the combinations randomly
for i in range(0, len(eta)):
    for j in range(0, len(phi)):
        prob = random() 
        if prob < 0.01:
            mapEtaf.write(str(eta[i]) + "\n") 
            mapPhif.write(str(phi[j]) + "\n") 
            mapHist.Fill(eta[i], phi[j])

outf.cd()
mapHist.Write()
outf.Close()
