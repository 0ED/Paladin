#! /usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2010 Peter Norvig. See http://norvig.com/lispy.html
# Copyright (c) 2014 TasukuTAKAHASHI.
#
# --- Sample Code ---
# (begin (define r 3) (* 3.141592653 (* r r)))
# (lambda (define r 3) (* 3.141592653 (* r r)))
#

import sys
from library_dict import LibraryDict

class Palisp:
	""" Palisp（Paladin用の中間コードを解釈するためのインタプリタ）
	"""
	
	def tokenize(self, a_statement):
		""" 文字列をトークンのリストに変換する。
		"""
		return a_statement.replace('(',' ( ').replace(')',' ) ').split()

	def string_to_number(self, a_token):
		""" 数は数にし、それ以外のトークンは文字列にする。正規表現で判定するよりも、Pythonの内部処理の方が速い。
		"""
		try:
			return int(a_token)
		except ValueError:
			try:
				return float(a_token)
			except ValueError:
				return str(a_token)

	def read_from(self, tokens):
		""" トークンの列から式を読み込む。
		"""
		if len(tokens) == 0:
			raise SyntaxError('unexpected EOF while reading')
		a_token = tokens.pop(0)
		if '(' == a_token:
			L = []
			while tokens[0] != ')':
				L.append(self.read_from(tokens))
			tokens.pop(0)
			return L
		elif ')' == a_token:
			raise SyntaxError('unexpected )')
		else:
			return self.string_to_number(a_token)

	def eval(self, tokens, a_dict):
		""" Evaluate an expression in an environment.
		"""
		if isinstance(tokens, str):
			return a_dict.find(tokens)[tokens]
		elif not isinstance(tokens, list):
			return tokens
		elif tokens[0] == 'quote':
			(_, exp) = tokens
			return exp
		elif tokens[0] == 'if':
			(_, test, conseq, alt) = tokens
			return self.eval((conseq if self.eval(test, a_dict) else alt), a_dict)
		elif tokens[0] == 'set!':
			(_, var, exp) = tokens
			a_dict.find(var)[var] = self.eval(exp, a_dict)
		elif tokens[0] == 'define':
			(_, var, exp) = tokens
			a_dict[var] = self.eval(exp, a_dict)
		elif tokens[0] == 'lambda':
			(_, vars, exp) = tokens
			return lambda *args: self.eval(exp, a_dict.update_dict(vars, args, a_dict))
		elif tokens[0] == 'begin':
			for exp in tokens[1:]:
				val = self.eval(exp,a_dict)
			return val
		else:
			exps = [self.eval(exp, a_dict) for exp in tokens]
			proc = exps.pop(0)
			return proc(*exps)

	def interpreter_one_line(self, a_line):
		""" 一行ずつインタプリタする。
		"""
		if a_line == "quit()":
			sys.exit(0)
		elif a_line == "":
			pass
		else:
			tokens = self.read_from(self.tokenize(a_line))
			a_string = self.eval(tokens, self._dict)
			if a_string != None:
				print a_string

	def talk(self):
		""" Palispインタプリタの対話モード。
		"""
		while True:
			a_line = raw_input("palisp > ")
			self.interpreter_one_line(a_line)

	def eat(self, filename):
		""" Palispインタプリタのイーティングモード。
		"""
		with open(filename, 'r') as a_file:
			a_line = a_file.readline()
			while a_line:
				self.interpreter_one_line(a_line)
				a_line = a_file.readline()

	def main(self):
		""" Palispインタプリタのメインルーチン。
		"""
		self._dict = LibraryDict()
		if len(sys.argv) == 1:
			self.talk()
		else:
			filename = sys.argv[1]
			self.eat(filename)
		return 0

if __name__ == '__main__':
	a_palisp = Palisp()
	sys.exit(a_palisp.main())

