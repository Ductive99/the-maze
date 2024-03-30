const TILE_SIZE = 64;
const ROWS = 11;
const COLS = 15;

const WINDOW_WIDTH = COLS * TILE_SIZE;
const WINDOW_HEIGHT = ROWS * TILE_SIZE;

const FOV_ANGLE = 60 * (Math.PI / 180);

const WALL_THICKNESS = 30;
const NUM_RAYS = WINDOW_WIDTH / WALL_THICKNESS;

class Map {
    constructor() {
        this.grid = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        ];
    }
    isBlocked(x, y) {
        if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
            return true;
        }
        var indexX = Math.floor(x / TILE_SIZE);
        var indexY = Math.floor(y / TILE_SIZE);
        return this.grid[indexY][indexX] != 0;
    }
    render() {
        for (var i = 0; i < ROWS; i++) {
            for (var j = 0; j < COLS; j++) {
                var tileX = j * TILE_SIZE; 
                var tileY = i * TILE_SIZE;
                var tileColor = this.grid[i][j] == 1 ? "#222" : "#fff";
                stroke("#222");
                fill(tileColor);
                rect(tileX, tileY, TILE_SIZE, TILE_SIZE);
            }
        }
    }
}

class Player {
    constructor() {
        this.x = WINDOW_WIDTH / 2;
        this.y = WINDOW_HEIGHT / 2;
        this.radius = 5;
        this.turnDirection = 0; /* -1 if left, +1 if right */
        this.walkDirection = 0; /* -1 if back, +1 if front */
        this.rotationAngle = Math.PI / 2;
        this.moveSpeed = 3.0;
        this.rotationSpeed = 3 * (Math.PI / 180);
    }
    update() {
        this.rotationAngle += this.turnDirection * this.rotationSpeed;

        var moveStep = this.walkDirection * this.moveSpeed;

        /* Player's next projected position*/
        var projX = this.x + Math.cos(this.rotationAngle) * moveStep;
        var projY = this.y + Math.sin(this.rotationAngle) * moveStep;

        if (!grid.isBlocked(projX, projY)) {
            this.x = projX;
            this.y = projY;
        }
    }
    render() {
        noStroke();
        fill("red");
        circle(this.x, this.y, this.radius);
        /*
        stroke("red");
        line(
            this.x,
            this.y,
            this.x + Math.cos(this.rotationAngle) * 30,
            this.y + Math.sin(this.rotationAngle) * 30
        );
        */
    }
}

class Ray {
    constructor(rayAngle) {
        this.rayAngle = normalize(rayAngle);
        this.wallHitX = 0;
        this.wallHitY = 0;
        this.distance = 0;

        this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
        this.isRayFacingUp = !this.isRayFacingDown;

        this.isRayFacingRight = this.rayAngle < 0.5 * Math.PI || this.rayAngle > 1.5 * Math.PI;
        this.isRayFacingLeft = !this.isRayFacingRight;
    }
    cast(columnId) {
        var xintercept, yintercept;
        var xstep, ystep;

        var wallIsHit = false;
        var wallHitX = 0;
        var wallHitY = 0;

        yintercept = Math.floor(player.y / TILE_SIZE) * TILE_SIZE;
        yintercept += this.isRayFacingDown ? TILE_SIZE : 0;

        xintercept = player.x + (yintercept - player.y) / Math.tan(this.rayAngle);

        ystep = TILE_SIZE;
        ystep *= this.isRayFacingUp ? -1 : 1;

        xstep = TILE_SIZE / Math.tan(this.rayAngle);
        xstep *= (this.isRayFacingLeft && xstep > 0) ? -1 : 1;
        xstep *= (this.isRayFacingRight && xstep < 0) ? -1 : 1;

        var nextIntrcptX = xintercept;
        var nextIntrcptY = yintercept;

        if (this.isRayFacingUp)
            nextIntrcptY--;

        while (nextIntrcptX >= 0 && nextIntrcptX <= WINDOW_WIDTH && nextIntrcptY >= 0 && nextIntrcptY <= WINDOW_HEIGHT) {
            if (grid.isBlocked(nextIntrcptX, nextIntrcptY)) {
                wallIsHit = true;
                wallHitX = nextIntrcptX;
                wallHitY = nextIntrcptY;

                stroke("red");
                line(player.x, player.y, wallHitX, wallHitY);

                break;
            } else {
                nextIntrcptX += xstep;
                nextIntrcptY += ystep;
            }
        }
    }
    render() { // Checked
        stroke("rgba(255, 0, 0, 0.1)");
        line(
            player.x,
            player.y,
            player.x + Math.cos(this.rayAngle) * 30,
            player.y + Math.sin(this.rayAngle) * 30
        );
    }
}

var grid = new Map();
var player = new Player();
var rays = [];

function keyPressed() { // Checked
    if (keyCode == UP_ARROW) {
        player.walkDirection = +1;
    } else if (keyCode == DOWN_ARROW) {
        player.walkDirection = -1;
    } else if (keyCode == RIGHT_ARROW) {
        player.turnDirection = +1;
    } else if (keyCode == LEFT_ARROW) {
        player.turnDirection = -1;
    }
}

function keyReleased() { // Checked
    if (keyCode == UP_ARROW) {
        player.walkDirection = 0;
    } else if (keyCode == DOWN_ARROW) {
        player.walkDirection = 0;
    } else if (keyCode == RIGHT_ARROW) {
        player.turnDirection = 0;
    } else if (keyCode == LEFT_ARROW) {
        player.turnDirection = 0;
    }
}

function castRays() { // Checked
    var columnId = 0;
    var rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

    rays = [];

    for (var i = 0; i < 1; i++) {
        var ray = new Ray(rayAngle);
        ray.cast(columnId);
        rays.push(ray);
        rayAngle += FOV_ANGLE / NUM_RAYS;
        columnId++;
    }
}

function normalize(angle) { // Checked
    angle = angle % (2 * Math.PI);
    if (angle < 0) {
        angle = (2 * Math.PI) + angle;
    }
    return angle;
}

function setup() { // Checked
    createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}

function update() { // Checked
    player.update();
}

function draw() { // Checked
    update();

    grid.render();
    for (ray of rays) {
        ray.render();
    }
    player.render();

    castRays();
}
