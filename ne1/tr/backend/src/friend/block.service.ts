import { Injectable } from '@nestjs/common';
import { FriendRepository } from "./friend.repository";
import { UserRepository } from "../user/user.repository";
import { Friend } from "./friend.entity";
import { User } from "../user/user.entity";
import { ConnectedSockets } from "../socket/connected-sockets.service";
import { UserService } from "../user/user.service";
import { GetUserDto } from "../dto/chat/get-user.dto";
import { BlockRepository } from "./block.repository";
import { GetBlockDto } from "../dto/get-block.dto";

@Injectable()
export class BlockService {
    constructor(
        private blockRepository: BlockRepository,
        private userRepository: UserRepository,
        private friendRepository: FriendRepository
    ) { }

    async addBlock(from: number, to: string) {
        const user = await this.userRepository.findUserById(from);
        const blockUser = await this.userRepository.findUserByUsername(to);

        if (user.blockList.map((block) => block.intraId).indexOf(blockUser.intraId) === -1) {
            await this.friendRepository.deleteFriendByUserIdIntraId(from, blockUser.intraId);

            await this.blockRepository.saveBlock(
                this.blockRepository.create({
                    intraId: blockUser.intraId,
                    username: blockUser.username,
                    user
                }),
            );
            return true;
        }
        return false;
    }

    async getAllBlock(id: number) {
        let blockName: GetBlockDto[] = [];
        const blocks = await this.blockRepository.findBlocksByUserId(id);
        for (const block of blocks) {
            const user = await this.userRepository.findUserByIntraId(block.intraId);
            blockName.push({
                id: block.id,
                username: user.username
            });
        }
        return blockName;
    }

    async deleteBlock(userId: number, friendId: number) {
        const blockName = (await this.blockRepository.findOneBy({ id: friendId }))
            .username;
        await this.blockRepository.deleteBlockByUser(userId, blockName);
    }
}
