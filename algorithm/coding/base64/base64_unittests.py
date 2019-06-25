import base64
import random
import unittest

import base64_c


def generate_random_bytes(size):
    return bytes(random.getrandbits(8) for _ in range(size))


class Base64UnitTest(unittest.TestCase):
    def setUp(self):
        self.ever_failed = (
            b'\x04B<\x96\xaa\x0e\xdae\x94U{\xd5]\xaat\xb6\xd5_',
            b'\x88\x1c\x95\x02\x16\xe7\x06\x8e\x1c\xaeC\xb2\x8b\x84\rm \xb3\xf6\x04J@\x1b\x91HV\xe0\xb3\xe1S\xbd\xf1g?\xcdv%P\xd0d\x0b\x1d\xdd\xbb\x17\x017c\\\xd1V\x8b\xe7\x05\x0f\x9bQ\x00km\x08\x9d\xc0\xea\xbb\xb6\xe5v3\x1e\xea\xb9\xac\xc6]\x02\x12\xad\xb3\x18D\x98Kt\xe5Ify\x90\'\xdd\xcf:-',
            b'X\xbbJ\xac\x9f\x0c\xda\xdf_^\xaf\xbab\xfdT\xa0\x0b',
            b'^\xf07\x18\nz\rS\xb4>\x1e\xf5>\xde\xc1\xa8\xcf\xa0',
            b'Kw\x05c\x9b\xe2\xf4\x07\x10\xa4$\xb9\x82V0\xc5\x9a',
            b'9\x83K?\xa5\x0b\xb6\xa7\xac\x02\xc8\x15+k\xc74a&\xb8\x97',
            b'\x9fl\x18\x11\xc4\xe0f=\x0b\x9cf\x15\xe9\x9a\x80\x91\x16\x13H\x9b',
            b'\xbe}\xa1+urf{\xa4\xb2&\xcf\xf5\xbe\xc7\r\xbf\x86',
            b'%\x9f\x88\x94\xa9\xc1\x08f-yG\x1d?P\x8d\xc0\xdak\xc9\xb9',
            b'P\xcau"w\xf1\xf7\xd5\xdb\x12\x97a\x92\xb0C',
            )
        self.data_list = [generate_random_bytes(random.randint(0, 20)) for _ in range(1000)]

    def test_ever_failed(self):
        for data in self.ever_failed:
            result1 = base64_c.base64_encode(data)
            result2 = base64.b64encode(data)
            self.assertEqual(result1, result2)

    def test_random_bytes(self):
        for data in self.data_list:
            result1 = base64_c.base64_encode(data)
            result2 = base64.b64encode(data)

            if result1 != result2:
                print(data)

            self.assertEqual(len(result1) % 4, 0)
            self.assertEqual(result1, result2)


if __name__ == '__main__':
    data = b'\x04B<\x96\xaa\x0e\xdae\x94U{\xd5]\xaat\xb6\xd5_'
    print(base64_c.base64_encode(data))
    print(base64.b64encode(data))

    data = b'%\x9f\x88\x94\xa9\xc1\x08f-yG\x1d?P\x8d\xc0\xdak\xc9\xb9'
    print(base64_c.base64_encode(data))
    print(base64.b64encode(data))

    unittest.main()


# References:
# https://stackoverflow.com/questions/5495492/random-byte-string-in-python
