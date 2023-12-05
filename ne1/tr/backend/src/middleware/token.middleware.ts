import { Injectable, NestMiddleware } from "@nestjs/common";
import { NextFunction, Request, Response } from "express";
import { UserRepository } from "../user/user.repository";

@Injectable()
export class TokenMiddleware implements NestMiddleware {
    constructor(private userRepository: UserRepository) {
    }
    
    async use(req: Request, res: Response, next: NextFunction) {
        const token = req.headers.authorization;
        console.log("middleware on");
        if (token) {
            const userId = req.params.id ? parseInt(req.params.id) : parseInt(req.body.userId);
            const userToken = (await this.userRepository.findUserById(userId)).token;
            if (userToken !== token) {
                res.status(401).json({ message : "token does not match" })
            }
            next();
        }
        else {
            res.status(401).json({ message: "token is invalid" })
        }
    }
}