function Test(a,b)
	return a + b, a - b, b - a
end

function Test2()
	return 2,3,4
end

function TestFunc(a,b)
	TestCFunc = 6
	return TestCFunc(a,b)
end

function TestRun()
	ang = VeAngle(0.5)
	print(ang,VeAngle.HALF_CYCLE)
	color = VeColor(0.1,0.2,0.3,1.0)
	color.r = 1.0
	print(VeColor.Mul(color,2),VeColor.WHITE)
end

function Tick()	
	print(VeTime.GetTime())
end

function TestEnum()
	print(VeDirectory.TYPE_ZIP.GetName())
	print(VeDirectory.Type.TYPE_ZIP.GetAlias())
	print(TEST_A.GetName())
	print(TEST_B.GetName())
	print(TestType.b.GetName())
end

function GetType()
	return VeDirectory.Type.TYPE_ZIP
end

VE_DIR = VeResourceManager.GetDir()

function LuaCall_LoadShaders()
	VeResourceManager.CreateGroup("Shaders", { VE_DIR.."Shaders" })
	VeResourceManager.CreateGroup("Sound", { VE_DIR.."Audio" })
	VeResourceManager.CreateGroup("Scripts", { VE_DIR.."Scripts" })
	VeResourceManager.CreateGroup("Textures", { VE_DIR.."Textures" })
	VeResourceManager.CreateGroup("Animation", { VE_DIR.."Animation" })
	VeResourceManager.CreateGroup("Fonts", { VE_DIR.."Fonts" })

	VeResourceManager.LoadVertexShader("draw_sprite_base", "Shaders")
	VeResourceManager.LoadPixelShader("draw_sprite_base", "Shaders")
	VeResourceManager.LoadVertexShader("draw_color_shape", "Shaders")
	VeResourceManager.LoadPixelShader("draw_color_shape", "Shaders")
	VeResourceManager.LoadVertexShader("draw_text", "Shaders")
	VeResourceManager.LoadPixelShader("draw_text", "Shaders")
end
