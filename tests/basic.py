import unittest

from asciistr import asciistr

class TestAsciiStrBasic(unittest.TestCase):
    def test_asciistr_from_str_plus_str(self):
        candidate = asciistr('hello') + 'world'
        self.assertEqual(candidate, 'helloworld')
        self.assertIs(type(candidate), str)

    def test_str_plus_asciistr_from_str(self):
        candidate = 'hello' + asciistr('world')
        self.assertEqual(candidate, 'helloworld')
        self.assertIs(type(candidate), str)

    def test_asciistr_from_bytes_plus_bytes(self):
        candidate = asciistr(b'hello') + b'world'
        self.assertEqual(candidate, b'helloworld')
        self.assertIs(type(candidate), bytes)

    def test_bytes_plus_asciistr_from_bytes(self):
        candidate = b'hello' + asciistr(b'world')
        self.assertEqual(candidate, b'helloworld')
        self.assertIs(type(candidate), bytes)

    def test_asciistr_will_not_accept_codepoints_above_127(self):
        self.assertRaises(ValueError, asciistr, 'Schrödinger')

if __name__ == '__main__':
    unittest.main()
