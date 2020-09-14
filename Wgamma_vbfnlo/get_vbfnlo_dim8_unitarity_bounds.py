#written by Rafael Coelho Lopes De Sa ‎[rafael.lopesdesa@cern.ch]‎

#!/bin/env python

import subprocess, sys, os, re, math

def writeConfig(operator, val):

    template = open('input_default.dat')
    steering = open('input.dat', 'w')

    for line in template:

        if operator in line:
            steering.write('%s          = %fd-12\n' % (operator, val))
        else:
            steering.write(line)

    template.close()
    steering.close()

def getLimit():

    retval = 14.
    p = subprocess.Popen(['./get-formfactor', 'input.dat'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    for line in out.splitlines():
        if 'FFscale_VVVV_Q_2' in line:
            retval = float(line.split()[-3])
        
    return retval

if __name__ == "__main__":
    
    listOperators = ['FW', 'FB', 'FWWW', 'FWT', 'FWWWT']
    maxTest       = [ 3,   51.,  51.,  1.5  24.]
    minTest       = [-3,  -51., -51., -1.5,-24.]
    limitOperator = {}
    
    for i, operator in enumerate(listOperators):
        upLimit = maxTest[i]
        downLimit = minTest[i]
        gotLimit = False
        theLimit = 0.
        precision = 0.
        thisTest = (upLimit+downLimit)/2.

        while not gotLimit:
            writeConfig(operator, thisTest)            
            theLimit = getLimit()

            print operator, thisTest, theLimit

            if theLimit == 14.:
                gotLimit = True
                limitOperator[operator] = thisTest

            elif theLimit > 14.:
                # O operador nao e grande o suficiente, aumenta
                downLimit = thisTest
                thisTest = (upLimit + thisTest)/2.

            elif theLimit < 14:
                # O operador ja violou unitariedade, diminui
                upLimit = thisTest
                thisTest = (downLimit + thisTest)/2.

    print limitOperator
