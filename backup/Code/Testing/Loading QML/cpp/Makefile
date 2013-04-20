HEADERS = $(wildcard *.h)

moc:
	$(foreach header, $(HEADERS), moc $(header) -o $(header:%.h=moc_%.cpp);)

clean:
	$(foreach header, $(HEADERS), rm $(header:%.h=moc_%.cpp);)
