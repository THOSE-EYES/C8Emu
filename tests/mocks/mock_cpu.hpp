// Include Gtest headers
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include project headers
#include "hw/cpu.hpp"

class MockCPU : public application::hw::CPU {
public:
	/**
	 * Mocking execute() method
	 */
	MOCK_METHOD1(execute, void(const Opcode&));

	/**
	 * Mocking interrupt() method
	 */
	MOCK_METHOD0(interrupt, void());

	/**
	 * Mocking ram() method
	 */
	MOCK_METHOD0(ram, std::shared_ptr<RAM>());

	/**
	 * Mocking gpu() method
	 */
	MOCK_METHOD0(gpu, std::shared_ptr<application::hw::GPU>());

	/**
	 * Mocking _0000() method
	 */
	MOCK_METHOD0(_0000, void());

	/**
	 * Mocking _00ee() method
	 */
	MOCK_METHOD0(_00ee, void());

	/**
	 * Mocking _00e0() method
	 */
	MOCK_METHOD0(_00e0, void());

	/**
	 * Mocking _1nnn() method
	 */
	MOCK_METHOD1(_1nnn, void(const Opcode&));

	/**
	 * Mocking _2nnn() method
	 */
	MOCK_METHOD1(_2nnn, void(const Opcode&));

	/**
	 * Mocking _3nnn() method
	 */
	MOCK_METHOD1(_3nnn, void(const Opcode&));

	/**
	 * Mocking _4xnn() method
	 */
	MOCK_METHOD1(_4xnn, void(const Opcode&));

	/**
	 * Mocking _5xy0() method
	 */
	MOCK_METHOD1(_5xy0, void(const Opcode&));

	/**
	 * Mocking _6xnn() method
	 */
	MOCK_METHOD1(_6xnn, void(const Opcode&));

	/**
	 * Mocking _7xnn() method
	 */
	MOCK_METHOD1(_7xnn, void(const Opcode&));

	/**
	 * Mocking _8xy0() method
	 */
	MOCK_METHOD1(_8xy0, void(const Opcode&));

	/**
	 * Mocking _8xy1() method
	 */
	MOCK_METHOD1(_8xy1, void(const Opcode&));

	/**
	 * Mocking _8xy2() method
	 */
	MOCK_METHOD1(_8xy2, void(const Opcode&));

	/**
	 * Mocking _8xy3() method
	 */
	MOCK_METHOD1(_8xy3, void(const Opcode&));

	/**
	 * Mocking _8xy4() method
	 */
	MOCK_METHOD1(_8xy4, void(const Opcode&));

	/**
	 * Mocking _8xy5() method
	 */
	MOCK_METHOD1(_8xy5, void(const Opcode&));

	/**
	 * Mocking _8xy6() method
	 */
	MOCK_METHOD1(_8xy6, void(const Opcode&));

	/**
	 * Mocking _8xy7() method
	 */
	MOCK_METHOD1(_8xy7, void(const Opcode&));

	/**
	 * Mocking _8xye() method
	 */
	MOCK_METHOD1(_8xye, void(const Opcode&));

	/**
	 * Mocking _9xy0() method
	 */
	MOCK_METHOD1(_9xy0, void(const Opcode&));

	/**
	 * Mocking _annn() method
	 */
	MOCK_METHOD1(_annn, void(const Opcode&));

	/**
	 * Mocking _bnnn() method
	 */
	MOCK_METHOD1(_bnnn, void(const Opcode&));

	/**
	 * Mocking _cxnn() method
	 */
	MOCK_METHOD1(_cxnn, void(const Opcode&));

	/**
	 * Mocking _dxyn() method
	 */
	MOCK_METHOD1(_dxyn, void(const Opcode&));

	/**
	 * Mocking _ex9e() method
	 */
	MOCK_METHOD1(_ex9e, void(const Opcode&));

	/**
	 * Mocking _exa1() method
	 */
	MOCK_METHOD1(_exa1, void(const Opcode&));

	/**
	 * Mocking _fx07() method
	 */
	MOCK_METHOD1(_fx07, void(const Opcode&));

	/**
	 * Mocking _fx0a() method
	 */
	MOCK_METHOD1(_fx0a, void(const Opcode&));

	/**
	 * Mocking _fx15() method
	 */
	MOCK_METHOD1(_fx15, void(const Opcode&));

	/**
	 * Mocking _fx18() method
	 */
	MOCK_METHOD1(_fx18, void(const Opcode&));

	/**
	 * Mocking _fx1e() method
	 */
	MOCK_METHOD1(_fx1e, void(const Opcode&));

	/**
	 * Mocking _fx29() method
	 */
	MOCK_METHOD1(_fx29, void(const Opcode&));

	/**
	 * Mocking _fx33() method
	 */
	MOCK_METHOD1(_fx33, void(const Opcode&));

	/**
	 * Mocking _fx55() method
	 */
	MOCK_METHOD1(_fx55, void(const Opcode&));

	/**
	 * Mocking _fx65() method
	 */
	MOCK_METHOD1(_fx65, void(const Opcode&));
};