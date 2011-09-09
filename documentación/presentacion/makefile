# makefile por Noelia Sales Montes

NOM = presentacion
PRES = ${NOM}.tex
PDF = ${NOM}.pdf

all: clean ${PDF}

pdf: ${PDF}

${PDF}: ${PRES}
	pdflatex --shell-escape ${PRES}
	pdflatex --shell-escape ${PRES}


clean: 
	rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg \
	*.log *.out *.snm *.nav *.vrb *~ ${PDF}