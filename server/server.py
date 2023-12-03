import asyncio
from websockets.server import serve
from serially import write_rotation

async def process(websocket):
    print("Connected")
    async for message in websocket:
        values = list(map(float, message.split("#")))
        x = values[0]
        y = values[1]
        z = values[2]
        print(z, y, x)
        write_rotation(y, z)


async def main():
    print("running")
    async with serve(process, "localhost", 8080):
        await asyncio.Future()  # run forever

asyncio.run(main())
