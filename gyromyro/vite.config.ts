import { sveltekit } from "@sveltejs/kit/vite";
import basicSsl from "@vitejs/plugin-basic-ssl";
import { defineConfig } from "vite";

export default defineConfig({
  server: {
    proxy: {
      "/socket": {
        target: "ws://localhost:8080/",
        ws: true,
      }
    },
  },
  plugins: [sveltekit(), basicSsl()],
});
