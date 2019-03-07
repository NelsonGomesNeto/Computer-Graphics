var reflections = 7, width = 800, widthDiv2 = 400, height = 800, heightDiv2 = 400;
var drawing = false, angle, pen, direction, speed, acceleration;

function setup() {
  width = window.innerWidth - 20, height = window.innerHeight - 40;
  widthDiv2 = width / 2, heightDiv2 = (height + 20) / 2;
  createCanvas(width, height, WEBGL);
  background(0, 0, 0);
  stroke(255, 255, 255); fill(255, 255, 255);
  pen = createVector(0, 0); direction = createVector(0, 0);
  speed = createVector(0, 0); acceleration = createVector(0, 0);

  reset = createButton("Reset");
  reset.position(20, 10);
  reset.mousePressed(clearScreen);
  textSize(20);
  penSize = createSlider(0.5, 40, 10);
  penSize.position(100, 10); text("penSize", 100, 40);
  reflectionsSlider = createSlider(0, 100, 7, 1);
  reflectionsSlider.position(250, 10); text("reflectionsSlider", 250, 40);
  speedLimit = createSlider(0.5, 20, 5);
  speedLimit.position(400, 10); text("speedLimit", 400, 40);
  accelerationLimit = createSlider(0.01, 5, 1);
  accelerationLimit.position(550, 10); text("accelerationLimit", 550, 40);
}

function clearScreen() {
  background(0, 0, 0);
}

function mousePressed() {
  pen.x = mouseX, pen.y = mouseY;
  drawing = true;
}

function mouseReleased() {
  drawing = false;
}

function update() {
  acceleration = createVector(mouseX, mouseY).sub(pen).normalize();
  acceleration.limit(accelerationLimit.value());
  speed.add(acceleration);
  speed.limit(speedLimit.value());
  pen.add(speed);
  strokeWeight(penSize.value());
}

function draw() {
  update();
  if (drawing) {
    // translate(widthDiv2, heightDiv2);
    reflections = reflectionsSlider.value();
    point(pen.x - widthDiv2, pen.y - heightDiv2);
    angle = 2*Math.PI / reflections;
    for (var i = 1; i <= reflections; i ++) {
      rotate(angle);
      point(pen.x - widthDiv2, pen.y - heightDiv2);
    }
  }
}