// Game Configuration
const CANVAS = document.getElementById('gameCanvas');
const CTX = CANVAS.getContext('2d');
const GAME_WIDTH = CANVAS.width;
const GAME_HEIGHT = CANVAS.height;

// Game Variables
let gameTime = 0;
let scoreA = 0;
let scoreB = 0;
let selectedPlayerTeam = null;
let selectedPlayerIndex = -1;

// Keyboard State
const keys = {};

// Player Class
class Player {
    constructor(x, y, number, teamColor) {
        this.x = x;
        this.y = y;
        this.number = number;
        this.color = teamColor;
        this.vx = 0;
        this.vy = 0;
        this.radius = 8;
        this.maxSpeed = 5;
        this.selected = false;
    }

    update(width, height) {
        this.x += this.vx;
        this.y += this.vy;
        this.vx *= 0.95;
        this.vy *= 0.95;

        if (this.x < this.radius) this.x = this.radius;
        if (this.x > width - this.radius) this.x = width - this.radius;
        if (this.y < this.radius) this.y = this.radius;
        if (this.y > height - this.radius) this.y = height - this.radius;
    }

    move(dx, dy) {
        this.vx += dx;
        this.vy += dy;
        const speed = Math.sqrt(this.vx * this.vx + this.vy * this.vy);
        if (speed > this.maxSpeed) {
            this.vx = (this.vx / speed) * this.maxSpeed;
            this.vy = (this.vy / speed) * this.maxSpeed;
        }
    }

    shoot(ball) {
        const dx = ball.x - this.x;
        const dy = ball.y - this.y;
        const distance = Math.sqrt(dx * dx + dy * dy);
        if (distance > 0) {
            ball.vx = (dx / distance) * 7;
            ball.vy = (dy / distance) * 7;
        }
    }

    draw(ctx) {
        ctx.beginPath();
        ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2);
        ctx.fillStyle = this.color;
        ctx.fill();
        
        if (this.selected) {
            ctx.strokeStyle = '#FFD700';
            ctx.lineWidth = 3;
        } else {
            ctx.strokeStyle = 'white';
            ctx.lineWidth = 2;
        }
        ctx.stroke();

        ctx.fillStyle = 'white';
        ctx.font = 'bold 10px Arial';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.fillText(this.number, this.x, this.y);
    }

    contains(x, y) {
        const dx = x - this.x;
        const dy = y - this.y;
        return Math.sqrt(dx * dx + dy * dy) <= this.radius + 5;
    }

    getBounds() {
        return {
            left: this.x - this.radius,
            right: this.x + this.radius,
            top: this.y - this.radius,
            bottom: this.y + this.radius
        };
    }
}

// Ball Class
class Ball {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.vx = 0;
        this.vy = 0;
        this.radius = 6;
        this.maxSpeed = 10;
    }

    update() {
        this.x += this.vx;
        this.y += this.vy;
        this.vx *= 0.98;
        this.vy *= 0.98;

        if (this.y <= this.radius || this.y >= GAME_HEIGHT - this.radius) {
            this.vy *= -0.8;
        }
        if (this.x <= this.radius) {
            this.vx *= -0.8;
            this.x = this.radius;
        }
        if (this.x >= GAME_WIDTH - this.radius) {
            this.vx *= -0.8;
            this.x = GAME_WIDTH - this.radius;
        }

        const speed = Math.sqrt(this.vx * this.vx + this.vy * this.vy);
        if (speed > this.maxSpeed) {
            this.vx = (this.vx / speed) * this.maxSpeed;
            this.vy = (this.vy / speed) * this.maxSpeed;
        }
    }

    bounce(playerX, playerY) {
        const dx = this.x - playerX;
        const dy = this.y - playerY;
        const distance = Math.sqrt(dx * dx + dy * dy);
        if (distance > 0.1) {
            this.vx = (dx / distance) * 6;
            this.vy = (dy / distance) * 6;
        }
    }

    reset(x, y) {
        this.x = x;
        this.y = y;
        this.vx = 0;
        this.vy = 0;
    }

    draw(ctx) {
        ctx.beginPath();
        ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2);
        ctx.fillStyle = 'white';
        ctx.fill();
        ctx.strokeStyle = '#000';
        ctx.lineWidth = 1;
        ctx.stroke();
    }

    getBounds() {
        return {
            left: this.x - this.radius,
            right: this.x + this.radius,
            top: this.y - this.radius,
            bottom: this.y + this.radius
        };
    }
}

// Team Class
class Team {
    constructor(name, color, startX) {
        this.name = name;
        this.color = color;
        this.startX = startX;
        this.players = [];
        this.initializeFormation();
    }

    initializeFormation() {
        this.players = [];

        // Goalkeeper
        const gkX = this.startX < GAME_WIDTH / 2 ? 30 : GAME_WIDTH - 30;
        this.players.push(new Player(gkX, GAME_HEIGHT / 2, 1, this.color));

        // Defenders (4)
        const defenseY = [100, 200, GAME_HEIGHT - 200, GAME_HEIGHT - 100];
        const defX = this.startX < GAME_WIDTH / 2 ? 150 : GAME_WIDTH - 150;
        for (let i = 0; i < 4; i++) {
            this.players.push(new Player(defX, defenseY[i], 2 + i, this.color));
        }

        // Midfielders (3)
        const midfieldY = [150, GAME_HEIGHT / 2, GAME_HEIGHT - 150];
        const midX = this.startX < GAME_WIDTH / 2 ? 400 : GAME_WIDTH - 400;
        for (let i = 0; i < 3; i++) {
            this.players.push(new Player(midX, midfieldY[i], 6 + i, this.color));
        }

        // Forwards (3)
        const forwardY = [120, GAME_HEIGHT / 2, GAME_HEIGHT - 120];
        const fwdX = this.startX < GAME_WIDTH / 2 ? 650 : GAME_WIDTH - 650;
        for (let i = 0; i < 3; i++) {
            this.players.push(new Player(fwdX, forwardY[i], 9 + i, this.color));
        }
    }

    update() {
        for (let player of this.players) {
            player.update(GAME_WIDTH, GAME_HEIGHT);
        }
    }

    selectPlayer(x, y) {
        for (let i = 0; i < this.players.length; i++) {
            if (this.players[i].contains(x, y)) {
                this.deselectAll();
                this.players[i].selected = true;
                return i;
            }
        }
        return -1;
    }

    deselectAll() {
        for (let player of this.players) {
            player.selected = false;
        }
    }

    moveSelected(dx, dy) {
        if (selectedPlayerIndex >= 0 && selectedPlayerTeam === this) {
            this.players[selectedPlayerIndex].move(dx, dy);
        }
    }

    shootWithSelected(ball) {
        if (selectedPlayerIndex >= 0 && selectedPlayerTeam === this) {
            this.players[selectedPlayerIndex].shoot(ball);
        }
    }

    draw(ctx) {
        for (let player of this.players) {
            player.draw(ctx);
        }
    }

    reset() {
        this.initializeFormation();
    }
}

// Initialize Game
const teamA = new Team('Team A', '#6496FF', 50);
const teamB = new Team('Team B', '#FF6464', GAME_WIDTH - 50);
const ball = new Ball(GAME_WIDTH / 2, GAME_HEIGHT / 2);

// Event Listeners
document.addEventListener('keydown', (e) => {
    keys[e.key.toLowerCase()] = true;

    if (e.key === 'r' || e.key === 'R') {
        resetGame();
    }
});

document.addEventListener('keyup', (e) => {
    keys[e.key.toLowerCase()] = false;
});

CANVAS.addEventListener('click', (e) => {
    const rect = CANVAS.getBoundingClientRect();
    const x = (e.clientX - rect.left) * (CANVAS.width / rect.width);
    const y = (e.clientY - rect.top) * (CANVAS.height / rect.height);

    let index = teamA.selectPlayer(x, y);
    if (index >= 0) {
        selectedPlayerTeam = teamA;
        selectedPlayerIndex = index;
        teamB.deselectAll();
    } else {
        index = teamB.selectPlayer(x, y);
        if (index >= 0) {
            selectedPlayerTeam = teamB;
            selectedPlayerIndex = index;
            teamA.deselectAll();
        }
    }
});

// Input Handling
function handleInput() {
    // Team A (WASD)
    if (keys['w']) teamA.moveSelected(0, -2);
    if (keys['s']) teamA.moveSelected(0, 2);
    if (keys['a']) teamA.moveSelected(-2, 0);
    if (keys['d']) teamA.moveSelected(2, 0);
    if (keys[' ']) teamA.shootWithSelected(ball);

    // Team B (Arrow Keys)
    if (keys['arrowup']) teamB.moveSelected(0, -2);
    if (keys['arrowdown']) teamB.moveSelected(0, 2);
    if (keys['arrowleft']) teamB.moveSelected(-2, 0);
    if (keys['arrowright']) teamB.moveSelected(2, 0);
    if (keys['enter']) teamB.shootWithSelected(ball);
}

// Collision Detection
function checkCollisions() {
    // Ball with Team A
    for (let player of teamA.players) {
        const pb = player.getBounds();
        const bb = ball.getBounds();
        if (!(pb.right < bb.left || pb.left > bb.right || pb.bottom < bb.top || pb.top > bb.bottom)) {
            ball.bounce(player.x, player.y);
        }
    }

    // Ball with Team B
    for (let player of teamB.players) {
        const pb = player.getBounds();
        const bb = ball.getBounds();
        if (!(pb.right < bb.left || pb.left > bb.right || pb.bottom < bb.top || pb.top > bb.bottom)) {
            ball.bounce(player.x, player.y);
        }
    }
}

// Goal Detection
function checkGoals() {
    const goalHeight = 100;
    const goalStartY = GAME_HEIGHT / 2 - 50;
    const goalEndY = GAME_HEIGHT / 2 + 50;

    // Goal for Team B (left side)
    if (ball.x < 5 && ball.y > goalStartY && ball.y < goalEndY) {
        scoreB++;
        resetBall();
        document.getElementById('scoreB').textContent = scoreB;
    }

    // Goal for Team A (right side)
    if (ball.x > GAME_WIDTH - 5 && ball.y > goalStartY && ball.y < goalEndY) {
        scoreA++;
        resetBall();
        document.getElementById('scoreA').textContent = scoreA;
    }
}

// Draw Pitch
function drawPitch() {
    // Background
    CTX.fillStyle = '#228B22';
    CTX.fillRect(0, 0, GAME_WIDTH, GAME_HEIGHT);

    // Center line
    CTX.strokeStyle = 'white';
    CTX.lineWidth = 2;
    CTX.beginPath();
    CTX.moveTo(GAME_WIDTH / 2, 0);
    CTX.lineTo(GAME_WIDTH / 2, GAME_HEIGHT);
    CTX.stroke();

    // Center circle
    CTX.beginPath();
    CTX.arc(GAME_WIDTH / 2, GAME_HEIGHT / 2, 40, 0, Math.PI * 2);
    CTX.stroke();

    // Center spot
    CTX.fillStyle = 'white';
    CTX.beginPath();
    CTX.arc(GAME_WIDTH / 2, GAME_HEIGHT / 2, 3, 0, Math.PI * 2);
    CTX.fill();

    // Goal areas
    CTX.strokeStyle = 'white';
    CTX.lineWidth = 2;
    CTX.strokeRect(10, GAME_HEIGHT / 2 - 75, 40, 150);
    CTX.strokeRect(GAME_WIDTH - 50, GAME_HEIGHT / 2 - 75, 40, 150);
}

// Game Loop
let lastTime = Date.now();
function gameLoop() {
    const currentTime = Date.now();
    const deltaTime = (currentTime - lastTime) / 1000;
    lastTime = currentTime;

    gameTime += deltaTime;
    document.getElementById('gameTime').textContent = formatTime(gameTime);

    handleInput();
    teamA.update();
    teamB.update();
    ball.update();
    checkCollisions();
    checkGoals();

    // Draw
    drawPitch();
    teamA.draw(CTX);
    teamB.draw(CTX);
    ball.draw(CTX);

    requestAnimationFrame(gameLoop);
}

// Helper Functions
function formatTime(seconds) {
    const mins = Math.floor(seconds / 60);
    const secs = Math.floor(seconds % 60);
    return `${String(mins).padStart(2, '0')}:${String(secs).padStart(2, '0')}`;
}

function resetBall() {
    ball.reset(GAME_WIDTH / 2, GAME_HEIGHT / 2);
}

function resetGame() {
    gameTime = 0;
    scoreA = 0;
    scoreB = 0;
    selectedPlayerTeam = null;
    selectedPlayerIndex = -1;
    teamA.reset();
    teamB.reset();
    ball.reset(GAME_WIDTH / 2, GAME_HEIGHT / 2);
    document.getElementById('scoreA').textContent = '0';
    document.getElementById('scoreB').textContent = '0';
}

// Start Game
gameLoop();
