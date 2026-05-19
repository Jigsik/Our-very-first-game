import { createServer } from "node:http";
import { createReadStream, statSync } from "node:fs";
import { extname, join, normalize, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const here = fileURLToPath(new URL(".", import.meta.url));
const repoRoot = resolve(here, "..");
const port = Number(process.env.PORT || 5177);

const types = new Map([
  [".html", "text/html; charset=utf-8"],
  [".js", "text/javascript; charset=utf-8"],
  [".css", "text/css; charset=utf-8"],
  [".png", "image/png"],
  [".gif", "image/gif"],
  [".txt", "text/plain; charset=utf-8"],
  [".wav", "audio/wav"],
  [".mp3", "audio/mpeg"]
]);

createServer((request, response) => {
  const url = new URL(request.url || "/", `http://localhost:${port}`);
  const requested = url.pathname === "/"
    ? "/v1-web/index.html"
    : url.pathname.endsWith("/")
      ? `${url.pathname}index.html`
      : url.pathname;
  const safePath = normalize(decodeURIComponent(requested)).replace(/^\.\.(\/|\\|$)/, "");
  const filePath = resolve(join(repoRoot, safePath));

  if (!filePath.startsWith(repoRoot)) {
    response.writeHead(403);
    response.end("Forbidden");
    return;
  }

  try {
    const stats = statSync(filePath);
    if (!stats.isFile()) throw new Error("Not a file");
    response.writeHead(200, {
      "content-type": types.get(extname(filePath).toLowerCase()) || "application/octet-stream",
      "cache-control": "no-store"
    });
    createReadStream(filePath).pipe(response);
  } catch {
    response.writeHead(404, { "content-type": "text/plain; charset=utf-8" });
    response.end(`Not found: ${requested}`);
  }
}).listen(port, () => {
  console.log(`v1 web running at http://localhost:${port}/v1-web/`);
});
