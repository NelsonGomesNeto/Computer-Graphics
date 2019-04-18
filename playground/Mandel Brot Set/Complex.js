class Complex {
  constructor(real, imaginary) {
    this.real = real;
    this.imaginary = imaginary;
  }

  add(other) {
    // if ((typeof other) === "object")
      this.real += other.real, this.imaginary += other.imaginary;
    // else
      // this.real += other;
    return(this);
  }

  mult(other) {
    // if ((typeof other) === "object") {
      let a = this.real, b = this.imaginary, c = other.real, d = other.imaginary;
      this.real = a*c - b*d, this.imaginary = a*d + b*c;
    // }
    // else
      // this.real *= other;
    return(this);
  }

  copy() {
    return(new Complex(this.real, this.imaginary));
  }
}