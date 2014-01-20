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

import math
import operator as op

class LibraryDict(dict):
	""" ペア{'var':val}のdictで、外部環境(outer)を持つ。
		"""
	def __init__(self, parms=(), args=(), outer=None):
		""" 初期化。
			"""
		self.update_dict(parms,args,outer)
		self.update(vars(math))
		operator_dict = {'+':op.add, '-':op.sub, '*':op.mul, '/':op.div, 'not':op.not_, '>':op.gt, '<':op.lt, '>=':op.ge, '<=':op.le, '=':op.eq, 'equal?':op.eq, 'eq?':op.is_, 'length':len, 'cons':lambda x,y:[x]+y, 'car':lambda x:x[0],'cdr':lambda x:x[1:], 'append':op.add, 'list':lambda *x:list(x), 'list?': lambda x:isa(x,list), 'null?':lambda x:x==[], 'symbol?':lambda x: isa(x, Symbol)}
		self.update(operator_dict)
	
	def update_dict(self, parms, args, outer):
		""" 辞書を更新する。
			"""
		self.outer = outer
		self.update(zip(parms,args))
	
	def find(self, var):
		""" Find the innermost Env where var appears.
			"""
		print var
		if var in self:
			return self
		else:
			print "変数" + str(var) + "が定義されていません。"
			return self
# self.outer.find(var)

