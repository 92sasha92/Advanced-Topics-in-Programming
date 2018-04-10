import unittest
from shutil import copyfile
import os


class TestStringMethods(unittest.TestCase):

    def test1(self):
        for i in range(1, 2):
            file1 = open("./rps.output")
            file2 = open("./tests/test_" + str(i) + "/rps.output")
            copyfile("./tests/test_" + str(i) + "/player1.rps_board", "./player1.rps_board")
            copyfile("./tests/test_" + str(i) + "/player2.rps_board", "./player2.rps_board")
            copyfile("./tests/test_" + str(i) + "/player1.rps_moves", "./player1.rps_moves")
            copyfile("./tests/test_" + str(i) + "/player2.rps_moves", "./player2.rps_moves")
            os.system("ex1")
            lines1 = file1.readlines()
            for j, lines2 in enumerate(file2):
                if lines2 != lines1[j]:
                    self.assertTrue(False)

            print "test_" + str(i) + " PASS"


if __name__ == '__main__':
    unittest.main()
