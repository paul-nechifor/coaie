const svg = document.getElementById('svg');
const pieces = document.getElementById('pieces');
const cellSize = parseInt(svg.getAttribute('width'), 10) / 15;

svg.onclick = function (ev) {
  const cellX = Math.floor(ev.offsetX / cellSize);
  const cellY = Math.floor(ev.offsetY / cellSize);
  const el = document.createElementNS('http://www.w3.org/2000/svg', 'use');
  const x = cellX * cellSize;
  const y = cellY * cellSize;
  el.setAttribute('transform', 'translate(' + x + ', ' + y + ')');
  el.setAttributeNS('http://www.w3.org/1999/xlink', 'href', '#Black01');
  pieces.appendChild(el);
};
