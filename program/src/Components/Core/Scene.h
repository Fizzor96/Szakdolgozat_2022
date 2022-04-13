#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
namespace eke
{
    enum class SceneId
    {
        Menu,
        Load,
        Main,
        Scoreboard,
        Credentials
    };

    class Scene
    {
    protected:
        eke::SceneId sceneid;

    public:
        Scene() {}
        virtual ~Scene() {}
        virtual eke::SceneId GetSceneId() const = 0;
        virtual void PollEvents() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void Restart(){};
    };

} // namespace eke

#endif // __SCENE_H__