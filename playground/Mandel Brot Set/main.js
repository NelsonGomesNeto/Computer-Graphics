let width = 1920, height = 1080;
var widthCenter, heightCenter;
let xMin = -2, xMax = 1, yMin = -1.2, yMax = 1.2;
let xScale, yScale;
let iterations = 10000;

function setup() {
  createCanvas(width, height); widthCenter = width * (abs(xMin) / (xMax - xMin)), heightCenter = height * (abs(yMin) / (yMax - yMin));
  xScale = width / (xMax - xMin), yScale = height / (yMax - yMin);
}

function f(c, z) {
  return(z.mult(z).add(c));
}

function drawGrid() {
  stroke(255, 0, 0);
  strokeWeight(1);
  fill(255, 0, 0);
  ellipse(0, 0, 5, 5);
  textSize(15); textAlign(LEFT, BOTTOM)
  for (var x = xMin; x <= xMax; x += 0.2) {
    text(x.toFixed(2), x * xScale, 0);
    line(x * xScale, yMin * yScale, x * xScale, yMax * yScale);
  }
  for (var y = yMin; y <= yMax; y += 0.2) {
    text(y.toFixed(2), 0, y * yScale);
    line(xMin * xScale, y * yScale, xMax * xScale, y * yScale);
  }
}

function drawMandelSteps() {
  stroke(0, 0, 100);
  strokeWeight(1);
  fill(0, 0, 100);

  var z = new Complex(0, 0), c = new Complex((xMax - xMin) * (mouseX - widthCenter) / width, (yMax - yMin) * (mouseY - heightCenter) / height);
  var points = []
  for (var i = 0; i < iterations; i ++) {
    z = f(c, z);
    // ellipse(z.real * xScale, z.imaginary * yScale, 10 - 5*(i / iterations), 10 - 5*(i / iterations));
    if (z.real < -1e6 || z.real > 1e6 || z.imaginary < -1e6 || z.imaginary > 1e6) break;
    points.push([z.real * xScale, z.imaginary * yScale]);
  }

  noFill();
  beginShape();
  curveVertex(points[0][0], points[0][1]);
  for (var i = 0; i < points.length; i ++) {
    curveVertex(points[i][0], points[i][1]);
  }
  curveVertex(points[points.length - 1][0], points[points.length - 1][1]);
  endShape();
}

function draw() {
  background(255, 255, 255);
  translate(widthCenter, heightCenter);

  drawGrid();

  drawMandelSteps();
}