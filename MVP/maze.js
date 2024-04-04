const TILE_SIZE = 64;
const ROWS = 11;
const COLS = 15;

const WINDOW_WIDTH = COLS * TILE_SIZE;
const WINDOW_HEIGHT = ROWS * TILE_SIZE;

const FOV_ANGLE = 70 * (Math.PI / 180);

const WALL_THICKNESS = 3;
const NUM_RAYS = WINDOW_WIDTH / WALL_THICKNESS;

const MINIMAP_FACTOR = 0.2;

class Map {
    constructor() {
        this.grid = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 3, 3, 3, 3, 3, 0, 0, 0, 2, 2, 2, 2, 0, 1],
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
    getGridVal(x, y) {
        if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
            return 0;
        var mapGridIndexX = Math.floor(x / TILE_SIZE);
        var mapGridIndexY = Math.floor(y / TILE_SIZE);
        return this.grid[mapGridIndexY][mapGridIndexX];
    }
    render() {
        for (var i = 0; i < ROWS; i++) {
            for (var j = 0; j < COLS; j++) {
                var tileX = j * TILE_SIZE; 
                var tileY = i * TILE_SIZE;
                var tileColor = this.grid[i][j] > 0 ? "#222" : "#fff";
                stroke("#222");
                fill(tileColor);
                rect(
                    MINIMAP_FACTOR * tileX,
                    MINIMAP_FACTOR * tileY,
                    MINIMAP_FACTOR * TILE_SIZE,
                    MINIMAP_FACTOR * TILE_SIZE
                );
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
        circle(
            MINIMAP_FACTOR * this.x,
            MINIMAP_FACTOR * this.y,
            MINIMAP_FACTOR * this.radius);

        stroke("blue");
        line(
            MINIMAP_FACTOR * this.x,
            MINIMAP_FACTOR * this.y,
            MINIMAP_FACTOR * this.x + Math.cos(this.rotationAngle) * 10,
            MINIMAP_FACTOR * this.y + Math.sin(this.rotationAngle) * 10
        );
    }
}

class Ray {
    constructor(rayAngle) {
        this.rayAngle = normalize(rayAngle);
        this.wallHitX = 0;
        this.wallHitY = 0;
        this.distance = 0;
        this.wasHitVertical = false;
        this.gridVal = 0;

        this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
        this.isRayFacingUp = !this.isRayFacingDown;

        this.isRayFacingRight = this.rayAngle < 0.5 * Math.PI || this.rayAngle > 1.5 * Math.PI;
        this.isRayFacingLeft = !this.isRayFacingRight;
    }
    cast() {
        var xintercept, yintercept;
        var xstep, ystep;

        /* HORIZONTAL RAY-GRID INTERSECTION */
        var horzWallIsHit = false;
        var horzWallHitX = 0;
        var horzWallHitY = 0;
        var horzWallColor = 0;

        yintercept = Math.floor(player.y / TILE_SIZE) * TILE_SIZE;
        yintercept += this.isRayFacingDown ? TILE_SIZE : 0;

        xintercept = player.x + (yintercept - player.y) / Math.tan(this.rayAngle);

        ystep = TILE_SIZE;
        ystep *= this.isRayFacingUp ? -1 : 1;

        xstep = TILE_SIZE / Math.tan(this.rayAngle);
        xstep *= (this.isRayFacingLeft && xstep > 0) ? -1 : 1;
        xstep *= (this.isRayFacingRight && xstep < 0) ? -1 : 1;

        var nextHtouchX = xintercept;
        var nextHtouchY = yintercept;

        while (nextHtouchX >= 0 && nextHtouchX <= WINDOW_WIDTH && nextHtouchY >= 0 && nextHtouchY <= WINDOW_HEIGHT) {
            var wallVal = grid.getGridVal(
                nextHtouchX,
                nextHtouchY - (this.isRayFacingUp ? 1 : 0)
            );
            if (wallVal != 0) {
                horzWallIsHit = true;
                horzWallHitX = nextHtouchX;
                horzWallHitY = nextHtouchY;
                horzWallColor = wallVal;
                break;
            } else {
                nextHtouchX += xstep;
                nextHtouchY += ystep;
            }
        }
        /* VERTICAL RAY-GRID INTERSECTION */
        var vertWallIsHit = false;
        var vertWallHitX = 0;
        var vertWallHitY = 0;
        var vertWallColor = 0;

        xintercept = Math.floor(player.x / TILE_SIZE) * TILE_SIZE;
        xintercept += this.isRayFacingRight ? TILE_SIZE : 0;

        yintercept = player.y + (xintercept - player.x) * Math.tan(this.rayAngle);

        xstep = TILE_SIZE;
        xstep *= this.isRayFacingLeft ? -1 : 1;

        ystep = TILE_SIZE * Math.tan(this.rayAngle);
        ystep *= (this.isRayFacingUp && ystep > 0) ? -1 : 1;
        ystep *= (this.isRayFacingDown && ystep < 0) ? -1 : 1;

        var nextVtouchX = xintercept;
        var nextVtouchY = yintercept;

        while (nextVtouchX >= 0 && nextVtouchX <= WINDOW_WIDTH && nextVtouchY >= 0 && nextVtouchY <= WINDOW_HEIGHT) {
            var wallVal = grid.getGridVal(
                nextVtouchX - (this.isRayFacingLeft ? 1 : 0),
                nextVtouchY
            );
            if (wallVal != 0) {
                vertWallIsHit = true;
                vertWallHitX = nextVtouchX;
                vertWallHitY = nextVtouchY;
                vertWallColor = wallVal;
                break;
            } else {
                nextVtouchX += xstep;
                nextVtouchY += ystep;
            }
        }
        var hHitDistance = (horzWallIsHit)
            ? distanceBtwn(player.x, player.y, horzWallHitX, horzWallHitY)
            : Number.MAX_VALUE;
        var vHitDistance = (vertWallIsHit)
            ? distanceBtwn(player.x, player.y, vertWallHitX, vertWallHitY)
            : Number.MAX_VALUE;

        this.wallHitX = (hHitDistance < vHitDistance) ? horzWallHitX : vertWallHitX;
        this.wallHitY = (hHitDistance < vHitDistance) ? horzWallHitY : vertWallHitY;
        this.distance = (hHitDistance < vHitDistance) ? hHitDistance : vHitDistance;
        this.gridVal = (hHitDistance < vHitDistance) ? horzWallColor : vertWallColor;
        this.wasHitVertical = (vHitDistance < hHitDistance);
    }
    render() {
        stroke("rgba(255, 0, 0, 0.2)");
        line(
            MINIMAP_FACTOR * player.x,
            MINIMAP_FACTOR * player.y,
            MINIMAP_FACTOR * this.wallHitX,
            MINIMAP_FACTOR * this.wallHitY
        );
    }
}

var grid = new Map();
var player = new Player();
var rays = [];

function keyPressed() {
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

function keyReleased() {
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

function render3D() {
    renderCeiling();
    renderFloor();

    for (var i = 0; i < NUM_RAYS; i++) {
        var ray = rays[i];
        var wallDistance = ray.distance * Math.cos(ray.rayAngle - player.rotationAngle);
        var projPlaneDistance = (WINDOW_WIDTH / 2) / Math.tan(FOV_ANGLE / 2);
        var wallHeight = (TILE_SIZE / wallDistance) * projPlaneDistance;

        var colorBrightness = ray.wasHitVertical ? 75 : 20;

        var colorR = ray.gridVal == 1 ? colorBrightness : 105;
        var colorG = ray.gridVal == 2 ? colorBrightness : 150;
        var colorB = ray.gridVal == 3 ? colorBrightness : 250;
        var shade = 1.0;

        fill(
            colorR,
            colorG,
            colorB,
            alpha
        )
        noStroke();
        rect(
            WALL_THICKNESS * i,
            (WINDOW_HEIGHT / 2) - (wallHeight / 2),
            WALL_THICKNESS,
            wallHeight
        );
    }
}

function castRays() {
    var rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

    rays = [];

    for (var i = 0; i < NUM_RAYS; i++) {
        var ray = new Ray(rayAngle);
        ray.cast();
        rays.push(ray);
        rayAngle += FOV_ANGLE / NUM_RAYS;
    }
}

function renderCeiling() {
    noStroke();
    fill('#73a4fa');
    rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT/2);
}

function renderFloor() {
    noStroke();
    fill('#273d2d');
    rect(0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT)
}

function normalize(angle) {
    return angle % (2 * Math.PI);
}

function distanceBtwn(x1, y1, x2, y2) {
    return Math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

function setup() {
    createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}

function update() {
    player.update();
    castRays();
}

function draw() {
    clear("#212121");
    update();

    render3D();

    grid.render();
    for (ray of rays) {
        ray.render();
    }
    player.render();
}
