import { TypeOrmModuleOptions } from '@nestjs/typeorm';

export const typeORMConfig: TypeOrmModuleOptions = {
    type: 'postgres',
    host: 'db',
    port: 5432,
    username: 'postgres',
    password: '1234',
    database: 'transcendence',
    entities: [__dirname + '/../**/*.entity.{js,ts}'],
    synchronize: true
}
