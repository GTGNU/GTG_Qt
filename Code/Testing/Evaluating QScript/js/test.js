var xs = []

for (var i = 0; i < 5000; i++) {
	x = {
		v: i,
		f: function() {
			var v0 = this.v;

			while (this.v > 0)
				this.v--;

			return v0
		}
	}

	xs.push(x.f());
}

var ys = []

for (var i = 0; i < xs.length; i++) {
	ys.push(xs[xs.length-i]);
}

qobjectTestObject.printWhatever("ys.length: " + ys.length);
