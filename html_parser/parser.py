import html2text
html = open("task7_instruction.html").read()
print html2text.html2text(html)