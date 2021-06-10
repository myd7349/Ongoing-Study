import faker

fake = faker.Faker('zh_CN')

for _ in range(10):
    print(f'{fake.name()}: {fake.address()}')
