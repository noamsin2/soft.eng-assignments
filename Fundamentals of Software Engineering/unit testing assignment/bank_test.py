# UNIT TEST
# Author: Noam Karasso
# Score: 98

import unittest
import bank as b


class TestBank(unittest.TestCase):
    def setUp(self):
        b.bank_accounts_money = [100, 0, 0, 0]

    def test_0_check_not_negative_or_zero(self):
        self.assertTrue(b.check_not_negative_or_zero(1))  # if x is positive -> return true
        self.assertFalse(b.check_not_negative_or_zero(0))  # if x is 0 -> return false
        self.assertFalse(b.check_not_negative_or_zero(-1))  # if x is negative -> return false

    def test_1_convert_to_number(self):
        self.assertEqual(b.convert_to_number(2.5), 2)  # if x can cast to int -> return the rounded value
        self.assertEqual(b.convert_to_number(-1.5), -1)  # if x can cast to int -> return the rounded value
        self.assertIsNone(b.convert_to_number('a'))  # if x can't cast to int -> return none

    def test_2_deposit(self):
        b.deposit(21.5)
        self.assertEqual(b.bank_accounts_money[0], 120, "should be 120")  # 21.5 adds total 20$ to account balance
        self.setUp()
        b.deposit('a')
        self.assertEqual(b.bank_accounts_money[0], 100)  # convert_to_number returns none,doesn't affect account balance
        b.deposit(-1)
        self.assertEqual(b.bank_accounts_money[0], 100)  # check_not_negative_or_zero returns none, doesn't affect account balance

    def test_3_withdraw(self):
        b.withdraw(21.5)
        self.assertEqual(b.bank_accounts_money[0], 78, "should be 78")  # 21.5 - 0.5 + 1(Fee) = 22
        self.setUp()
        b.withdraw('a')
        self.assertEqual(b.bank_accounts_money[0], 100)  # convert_to_number returns none,doesn't affect account balance
        b.withdraw(-1)
        self.assertEqual(b.bank_accounts_money[0], 100)  # check_not_negative_or_zero returns none, doesn't affect account balance
        b.withdraw(101)
        self.assertEqual(b.bank_accounts_money[0], 100)  # can't withdraw more than account balance, balance left unchanged

    def test_4_transfer(self):
        b.transfer(1, 'a')
        self.assertEqual(b.bank_accounts_money[1], 0)  # convert_to_number returns none, balance left unchanged
        b.transfer(1, 100)
        self.assertEqual(b.bank_accounts_money[1], 0)  # withdraw_check_balance returns false, balance left unchanged
        b.transfer(1, -1)
        self.assertEqual(b.bank_accounts_money[1], 0)  # check_not_negative_or_zero returns false,balance left unchanged
        b.transfer(5, 20)
        self.assertEqual(b.bank_accounts_money[0], 100)  # index 5 > len (account doesn't exist)
        b.transfer(0, 20)
        self.assertEqual(b.bank_accounts_money[0], 100, "should be 100")  # should be impossible to transfer to yourself
        self.setUp()
        b.transfer(3, 20)
        self.assertEqual(b.bank_accounts_money[3], 20)  # +20$ to account #3
        self.assertEqual(b.bank_accounts_money[0], 79)  # -(20$ + 1$ FEE) to own account
        self.setUp()

    def test_5_Withdraw_check_balance(self):
        self.assertTrue(b.withdraw_check_balance(99))  # amount+fee = balance -> returns true
        self.assertFalse(b.withdraw_check_balance(100))  # amount+fee > balance -> returns false
        self.assertTrue(b.withdraw_check_balance(98))  # amount+fee < balance -> returns true
