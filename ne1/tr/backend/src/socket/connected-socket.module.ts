import { ConnectedSockets } from "./connected-sockets.service";
import { Module } from "@nestjs/common";

@Module({
    imports: [],
    controllers: [],
    providers: [ConnectedSockets],
    exports: [ConnectedSockets]
})
export class ConnectedSocketModule {}
