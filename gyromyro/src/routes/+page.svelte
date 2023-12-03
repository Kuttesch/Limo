<script lang="ts">
  import { page } from "$app/stores";

  let gyro = new Gyroscope({ frequency: 60 });

  let x = 0,
    y = 0,
    z = 0;

  gyro.addEventListener("reading", () => {
    x += gyro.x;
    y += gyro.y;
    z += gyro.z;
  });

  setInterval(() => {
    if (websocket)
      websocket.send(`${x}#${y}#${z}`);
  }, 1000)

  gyro.start();

  let websocket: WebSocket | null = null;
  const reporter_url = "wss://" + $page.url.host + "/socket";

  function run() {
    if (!websocket) {
      websocket = new WebSocket(reporter_url);
    }
  }
</script>

<p>X: {Math.round(x)} | Y: {Math.round(y)} | Z: {Math.round(z)}</p>

<div class="container">
  <div class="surface" style="--x:{x}deg;--y:{y}deg;--z:{z}deg"></div>
</div>
<button on:click={run}>Connect</button>

<style>
  :global(body) {
    background: #111;
    overflow-x: hidden;
  }
  button {
    background-color: red;
    border-radius: 10px;
    padding: 20px 40px;
    border: none;
    margin-left: auto;
    margin-right: auto;
    display: block;
    margin-bottom: 40px;
  }
  * {
    font-family: sans-serif;
  }
  p {
    color: white;
  }
  .container {
    width: 100%;
    height: calc(100vh - 300px);
    display: grid;
    perspective: 1000px;
    perspective-origin: 50% 50%;
    place-items: center;
  }
  .surface {
    transform: rotateX(var(--x)) rotateY(var(--y)) rotateZ(var(--z));
    background: linear-gradient(to bottom, #333, #aaa);
    width: 80%;
    height: 80%;
  }
</style>
