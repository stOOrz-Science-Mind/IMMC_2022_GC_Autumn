import core5
import sys
from PyQt4 import QtCore, QtGui, uic

qtCreatorFile = "ui.ui"

Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

class Decition(QtGui.QMainWindow, Ui_MainWindow, QtGui.QTableWidget):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)
        self.Calculate.clicked.connect(self.CalculatePcs)

    def CalculatePcs(self):
        r = float(self.r.text())
        z = float(self.z.text())
        w = float(self.w.text())
        Pm = float(self.Pm.text())
        Pw = float(self.Pw.text())
        n = int(self.n.text())
        R = float(self.R.text())
        C = core5.C(r,z,w,n)
        A = core5.A(Pm,Pw,n)
        if C*(R+1) > A > C:
            Committee = QtGui.QTableWidgetItem("Deal")
            Insurer = QtGui.QTableWidgetItem("Deal")
        if C > A:
            Committee = QtGui.QTableWidgetItem("Should not")
            Insurer = QtGui.QTableWidgetItem("Should")
        if A > C*(R+1):
            Committee = QtGui.QTableWidgetItem("Should")
            Insurer = QtGui.QTableWidgetItem("Should not")
        ResultA = QtGui.QTableWidgetItem("%d" %A)
        self.ResultTable.insertRow(0)
        self.ResultTable.setItem(0, 0, ResultA)
        self.ResultTable.setItem(0, 1, Committee)
        self.ResultTable.setItem(0, 2, Insurer)

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    window = Decition()
    window.show()
    sys.exit(app.exec_())