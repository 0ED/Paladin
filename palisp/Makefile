PYCS	= \
	palisp.pyc \
	library_dict.pyc 
PYS		= $(PYCS:%.pyc=%.py)

test:
	python palisp.py demo/a.pp
talk:
	python palisp.py
clean:
	$(RM) $(PYCS)
open:
	vim $(PYS)
