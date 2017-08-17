const $ = require('jquery');
const _ = require('underscore');
const path = require('path');
const {exec} = require('child_process');

const $svg = $('#svg');
const $pieces = $('#pieces');
const cellSize = parseInt(svg.getAttribute('width'), 10) / 15;
const board = _.range(15 * 15).map(x => 0);
const code = {'-1': 'o', '0': '.', '1': 'x'};

let playerColor = 1;

function renderBoard() {
  $pieces.empty();

  for (let i = 0; i < 15; i++) {
    for (let j = 0; j < 15; j++) {
      const player = board[i * 15 + j];
      if (player) {
        addPiece(i, j, player);
      }
    }
  }
}

function addPiece(i, j, player) {
  const el = document.createElementNS('http://www.w3.org/2000/svg', 'use');
  const x = j * cellSize;
  const y = i * cellSize;
  const color = player == 1 ? '#Black01' : '#White01';
  el.setAttribute('transform', 'translate(' + x + ', ' + y + ')');
  el.setAttributeNS('http://www.w3.org/1999/xlink', 'href', color);
  $pieces.append(el);
}

$svg.click(ev => {
  const i = Math.floor(ev.offsetY / cellSize);
  const j = Math.floor(ev.offsetX / cellSize);
  board[i * 15 + j] = playerColor;
  renderBoard();

  const aiPlayer = -playerColor;
  const str = board.map(x => code[x]).join('');
  const exe = path.resolve(__dirname, 'coaie');
  const cmd = `${exe} play ${str} ${code[playerColor]}`;
  exec(cmd, {encoding: 'utf8'}, (err, out) => {
    const list = out.trim().split(' ');
    const move = parseInt(list[Math.floor(Math.random() * list.length)], 10);
    board[move] = -playerColor;
    renderBoard();
  });
});

renderBoard();
