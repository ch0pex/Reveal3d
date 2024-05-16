

#include "core/scene.hpp"
#include "render/viewport.hpp"
#include "math/math.hpp"

#include "Samples/common/scripts.hpp"

using namespace reveal3d;
using namespace reveal3d::graphics;


LogLevel loglevel = logDEBUG;

_Use_decl_annotations_
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    {
        Timer timer;
        f32 time = timer.TotalTime();
        window::InitInfo windowInitInfo(L"Reveal3d", 1920, 1080);
        render::Viewport<dx::Graphics, window::Win32> viewport(windowInitInfo);

        core::Entity human = core::scene.AddEntityFromObj(L"Assets/humano.obj");
        core::scene.AddPrimitive(reveal3d::core::Geometry::cube);

        for (u32 i = 0; i < 10; ++i) {
            for (u32 j = 0; j < 10; ++j) {
                for (u32 k = 0; k < 20; ++k) {
                    core::EntityInfo info = {
                            core::Transform({i * 1.5f, j * 1.5f, 1.5f * k}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}),
                            human.GetGeometry()};
                    core::Entity entity = core::scene.AddEntity(info);
                    entity.AddScript<HumanScript>();

                }
            }
        }

        viewport.Init();
        log(logDEBUG) << "Total Init time: " << timer.Diff(time);
        viewport.Run();

    }
#ifdef _DEBUG
//    graphics::dx::utl::ReportLiveDeviceObjs();
#endif
    return 0;
}