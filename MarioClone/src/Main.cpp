#include "Main.h"

int main()
{
    // init
    SDL_Window* mainWin;
    GLHandler::Init(mainWin);

    GameObject object;
    Input input(object);
    SpriteRenderer *renderer;

    // load shaders
    ResourceManager::LoadShader("src/shaders/vert/SpriteVert.vert", "src/shaders/frag/SpriteFrag.frag", nullptr, "sprite");

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    renderer = new SpriteRenderer(shader);

    // load textures
    ResourceManager::LoadTexture("assets/sprites/player/Player.png", true, "player");

    // time variables
    const double dt = 6;
    double accumulatedTime = 0;
    double lastTime = SDL_GetTicks();
    double currentTime;

    // set up our event handler
    while (1)
    {
        currentTime = SDL_GetTicks();
        accumulatedTime += currentTime - lastTime;
        lastTime = currentTime;

        // loops through all events and input
        input.HandleInput();

        while (accumulatedTime > dt)
        {
            // Update(dt)
            accumulatedTime -= dt;
        }

        // RENDERING
        Texture2D texture = ResourceManager::GetTexture("player");
        renderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    GLHandler::Destroy(mainWin);
    return 0;
}